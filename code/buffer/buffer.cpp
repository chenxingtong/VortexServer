/*
 * @Date: 2022-10-09 20:50:07
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-10-28 22:45:00
 * @FilePath: /VortexServer/code/buffer/buffer.cpp
 */
#include "buffer.h"

#include <cstddef>
using namespace std;

Buffer::Buffer(int initBufferSize) : buffer(initBufferSize), readPos(0), writePos(0) {}