/*
 * @Date: 2022-11-11 08:29:02
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-11 15:58:37
 * @FilePath: /VortexServer/code/http/httpconnect.cpp
 */
#include "httpconnect.h"
#include <atomic>
#include <cassert>

using namespace std;

atomic<int> HttpConnect::userCnt;

HttpConnect::HttpConnect()
{
  fd = 1;
  addr = {0};
  isClose = true;
}

void HttpConnect::init(int fd, const sockaddr_in addr)
{
  assert(fd > 0);
  userCnt++;
  this->addr = addr;
  this->fd = fd;
  writeBuffer.retrieveAll();
  readBuffer.retrieveAll();
  isClose = false;
  LOG_INFO("Client[%d](%s:%d)in,userCount:%d", fd, getIP(), getPort(), (int)userCnt);
  //资源响应
  request.init();   //解析请求行等初始化
}

void HttpConnect::closeConnect()
{
  //
}