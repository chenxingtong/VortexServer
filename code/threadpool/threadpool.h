#ifndef THREADPOOL_H
#define THREADPOOL_H
/*
 * @Date: 2022-11-09 09:34:57
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-09 11:26:50
 * @FilePath: /VortexServer/code/threadpool/threadpool.h
 */
#include "../lock/locker.h"
#include <assert.h>
#include <functional>
#include <memory>
#include <queue>
#include <thread>

using namespace std;

class ThreadPool
{
public:
  static ThreadPool* instance()
  {
    static ThreadPool threadpool;
    return &threadpool;
  }
  void init(int threadNumber = 8, int maxRequests = 10000)
  {
    this->threadNumber = threadNumber;
    this->maxRequests = maxRequests;
    assert(threadNumber > 0);
    //初始化后要做线程的分离
    for (int i = 0; i < threadNumber; i++)
    {
      thread(callback, this).detach();
    }
  }
  //添加回调函数
  static void callback(ThreadPool* pool)
  {
    while (true)
    {
      pool->mtxPool.lock();
      //此处需要function<void>
      // 如果列表为空且未停止，先阻塞。
      while (pool->tasks.empty() && !pool->shutdown)
      {
        pool->condNoempty.wait(pool->mtxPool.get());
      }
      if (pool->shutdown)
      {
        pool->mtxPool.unlock();
        break;
      }
      auto task = move(pool->tasks.front());
      pool->tasks.pop();
      pool->mtxPool.unlock();
      task();
    }
  }

private:
  ThreadPool() {}
  ~ThreadPool()
  {
    mtxPool.lock();
    shutdown = true;
    mtxPool.unlock();
    condNoempty.broadcast();
  }

private:
  int threadNumber;
  int maxRequests;
  mtx mtxPool;
  //函数指针 task是queue，调用queue函数
  queue<function<void()>> tasks;
  bool shutdown;
  cond condNoempty;
};
#endif
