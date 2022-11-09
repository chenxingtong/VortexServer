/*
 * @Date: 2022-11-09 11:32:27
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-09 11:34:42
 * @FilePath: /VortexServer/code/http/httppresponse.h
 */
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unordered_map>

#include "../buffer/buffer.h"
#include "../log/log.h"

using namespace std;

class HttpResponse
{
  HttpResponse();
  ~HttpResponse();
  void init();
};
#endif