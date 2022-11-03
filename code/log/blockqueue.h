/*
 * @Date: 2022-11-03 03:40:13
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-03 14:35:15
 * @FilePath: /VortexServer/code/log/blockqueue.h
 */

/*
阻塞队列，封装了生产者消费者模型，
 */

#ifndef BLOCKQUEUE_H
#define BLOCKQUEUE_H
#include <cstddef>
#include <sys/time.h>

#include <cassert>
#include <condition_variable>
#include <mutex>
#include <queue>

template<class T> class BlockQueue
{
public:
  explicit BlockQueue(size_t MaxCapacity = 1000);
  ~BlockQueue();
  void close();

  //几种方法
  void clear();
  bool empty();
  bool full();
  size_t size();
  size_t capacity();   //容量
  void flush();        //唤醒一个
  T front();
  T back();
  void push(const T& item);
  bool pop(T& item);
  bool pop(T& item, int timeout);

private:
  size_t m_capacity;
  bool isClose = false;
  std::mutex m_mutex;
  std::condition_variable condConsumer;
  std::condition_variable condProducer;
  std::queue<T> que;
};

template<class T> BlockQueue<T>::BlockQueue(size_t MaxCapacity) : m_capacity(MaxCapacity)
{
  assert(MaxCapacity > 0);
  isClose = false;
}
template<class T> BlockQueue<T>::~BlockQueue()
{
  close();
};
template<class T> void BlockQueue<T>::close()
{
  {
    std::lock_guard<std::mutex> locker(m_mutex);
    que = std::queue<T>();
    isClose = true;
  }
  condProducer.notify_all();
  condConsumer.notify_all();
};
// 几种方法的实现
template<class T> void BlockQueue<T>::clear()
{
  std::lock_guard<std::mutex> locker(m_mutex);
  que.clear();   // queue不支持clear
}

template<class T> bool BlockQueue<T>::empty()
{
  std::lock_guard<std::mutex> locker(m_mutex);
  return que.empty();
}

template<class T> size_t BlockQueue<T>::capacity()
{
  std::lock_guard<std::mutex> locker(m_mutex);
  return m_capacity;
}

template<class T> size_t BlockQueue<T>::size()
{
  std::lock_guard<std::mutex> locker(m_mutex);
  return que.size();
}

template<class T> bool BlockQueue<T>::full()
{
  //调用size函数，得到的结果大于目前的容量
  std::lock_guard<std::mutex> locker(m_mutex);
  return que.size() >= m_capacity;
}

template<class T> void BlockQueue<T>::flush()
{
  condConsumer.notify_one();
};

// front and back
template<class T> T BlockQueue<T>::front()
{
  std::lock_guard<std::mutex> locker(m_mutex);
  return que.front();
}

template<class T> T BlockQueue<T>::back()
{
  std::lock_guard<std::mutex> locker(m_mutex);
  return que.back();
}

// push and pop
template<class T> void BlockQueue<T>::push(const T& item)
{
  std::unique_lock<std::mutex> locker(m_mutex);
  while (que.size() >= capacity())
  {
    condProducer.wait(locker);
  }
  que.push(item);
  condConsumer.notify_one();
}

template<class T> bool BlockQueue<T>::pop(T& item)
{
  std::unique_lock<std::mutex> locker(m_mutex);
  while (que.empty())
  {
    condConsumer.wait(locker);
    if (isClose)
    {
      return false;
    }
  }
  item = que.front();
  que.pop();
  condProducer.notify_one();
  return true;
}

template<class T> bool BlockQueue<T>::pop(T& item, int timeout)
{
  std::unique_lock<std::mutex> locker(m_mutex);
  while (que.empty())
  {
    //判断等待时间是否超过timeout
    if (condConsumer.wait_for(locker, std::chrono::seconds(timeout)) == std::cv_status::timeout)
    {
      return false;
    }
    if (isClose)
    {
      return false;
    }
  }
  item = que.front();
  que.pop();
  condProducer.notify_one();
  return true;
}

#endif
