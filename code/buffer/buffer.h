/*
 * @Date: 2022-10-09 09:53:27
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-10-28 13:49:45
 * @FilePath: /VortexServer/code/buffer/buffer.h
 */

#ifndef BUFFER_H
#define BUFFER_H
#include <sys/uio.h>
#include <unistd.h>

#include <atomic>
#include <cassert>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <vector>

using namespace std;

class Buffer
{
public:
  Buffer(int initBufferSize = 1024);
  ~Buffer() = default;

private:
  vector<char> buffer;
  atomic<size_t> readPos;
  atomic<size_t> writePos;
};
#endif