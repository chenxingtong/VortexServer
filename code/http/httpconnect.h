/*
 * @Date: 2022-11-10 00:00:49
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-12-08 07:57:20
 * @FilePath: /VortexServer/code/http/httpconnect.h
 */
#ifndef HTTPCONNECT_H
#define HTTPCONNECT_H

#include <arpa/inet.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>

#include "../buffer/buffer.h"
#include "../log/log.h"
#include "../sqlconnpool/sql_conn_pool.h"
#include "httprequest.h"
#include "httpresponse.h"

using namespace std;

class HttpConnect
{
public:
  HttpConnect();
  ~HttpConnect() { closeConnect(); }

  void init(int sockfd, const sockaddr_in& addr);

  ssize_t read(int* saveErrno);
  ssize_t write(int* saveErrno);

  void closeConnect();

  int getfd() const { return fd; }
  sockaddr_in getAddr() const { return addr; }
  int getPort() const { return addr.sin_port; }
  const char* getIP() const { return inet_ntoa(addr.sin_addr); }

  bool process();

  int toWriteBytes() { return iov[0].iov_len + iov[1].iov_len; }

  bool isKeepAlive() const { return request.isKeepAlive(); }

  static bool isET;
  static const char* srcDir;
  static atomic<int> userCnt;

private:
  int fd;
  struct sockaddr_in addr;

  bool isClose;

  int iovCnt;
  struct iovec iov[2];

  Buffer readBuffer;
  Buffer writeBuffer;

  HttpRequest request;
  HttpResponse response;
};

#endif