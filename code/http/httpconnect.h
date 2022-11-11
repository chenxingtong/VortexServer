/*
 * @Date: 2022-11-10 00:00:49
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-11 15:56:42
 * @FilePath: /VortexServer/code/http/httpconnect.h
 */
#ifndef HTTPCONNECT_H
#define HTTPCONNECT_H
//#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>

#include "../buffer/buffer.h"
#include "../log/log.h"
#include "../sql_conn_pool/sql_conn_pool.h"
#include "httpprequest.h"
#include "httppresponse.h"
using namespace std;

class HttpConnect
{
public:
  HttpConnect();
  ~HttpConnect() { closeConnect(); }
  void init(int fd, const sockaddr_in addr);
  void closeConnect();

public:
  static atomic<int> userCnt;
  const char* getIP() const { return inet_ntoa(addr.sin_addr); }
  int getPort() { return addr.sin_port; }
  int getfd() const { return fd; }
  sockaddr_in getAddr() const { return addr; }

private:
  int fd;
  struct sockaddr_in addr;
  bool isClose;
  Buffer readBuffer;
  Buffer writeBuffer;
  HttpRequest request;
  HttpResponse response;
};


#endif