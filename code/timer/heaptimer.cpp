/*
 * @Date: 2022-11-15 02:18:33
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-16 10:59:03
 * @FilePath: /VortexServer/code/timer/heaptimer.cpp
 */
#include "heaptimer.h"
void HeapTimer::swapNode(size_t i, size_t j)
{
  size_t s = heap.size();
  assert(i >= 0 && i < s);
  assert(j >= 0 && j < s);
  std::swap(heap[i], heap[j]);
  ref[heap[i].id] = i;
  ref[heap[j].id] = j;
}

void HeapTimer::siftup(size_t i)
{
  assert(i >= 0 && i < heap.size());

  size_t j = (i - 1) / 2;
  while (j >= 0 && heap[i] < heap[j])
  {
    swapNode(i, j);
    i = j;
    j = (i - 1) / 2;
  }
}

void HeapTimer::siftdown(size_t i)
{
  size_t s = heap.size();
  assert(i >= 0 && i < s);
  size_t t = i * 2 + 1;

  while (t < s)
  {
    if (t + 1 < s && heap[t + 1] < heap[t]) t++;
    if (heap[i] < heap[t]) break;
    swap(heap[i], heap[t]);
    i = t, t = i * 2 + 1;
  }
}

void HeapTimer::add(int id, int timeout, const TimeoutCallBack& cb)
{
  assert(id >= 0);
  size_t i;
  if (!ref.count(id))
  {
    i = heap.size();
    ref[id] = i;
    heap.push_back({id, Clock::now() + MS(timeout), cb});
    siftup(i);
  }
  else
  {
    i = ref[id];
    heap[i].expires = Clock::now() + MS(timeout);
    heap[i].cb = cb;
    siftdown(i);
    siftup(i);
  }
}

void HeapTimer::del(size_t i)
{
  assert(!heap.empty() && i >= 0 && i < heap.size());
  size_t n = heap.size() - 1;
  swapNode(i, n);

  ref.erase(heap.back().id);
  heap.pop_back();
  //如果堆空就不用调整了
  if (!heap.empty())
  {
    siftdown(i);
    siftup(i);
  }
}

void HeapTimer::adjust(int id, int timeout)
{
  assert(!heap.empty() && ref.count(id));
  heap[ref[id]].expires = Clock::now() + MS(timeout);
  siftdown(ref[id]);
  siftup(ref[id]);
}

void HeapTimer::tick()
{
  if (heap.empty()) return;

  while (!heap.empty())
  {
    TimerNode node = heap.front();

    if (std::chrono::duration_cast<MS>(node.expires - Clock::now()).count() > 0)
    {
      break;
    }
    node.cb();
    pop();
  }
}

void HeapTimer::pop()
{
  assert(!heap.empty());
  del(0);
}

void HeapTimer::clear()
{
  ref.clear();
  heap.clear();
}

int HeapTimer::getNextTick()
{
  //处理堆顶计时器，若超时执行回调再删除
  tick();
  size_t res = -1;
  if (!heap.empty())
  {
    //计算现在堆顶的超时时间，到期时先唤醒一次epoll，判断是否有新事件（即便已经超时）
    res = std::chrono::duration_cast<MS>(heap.front().expires - Clock::now()).count();
    if (res < 0)
    {
      res = 0;
    }
  }
  return res;
}