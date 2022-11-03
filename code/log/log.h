/*
 * @Date: 2022-10-09 09:19:10
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-03 14:53:54
 * @FilePath: /VortexServer/code/log/log.h
 */
#ifndef LOG_H
#define LOG_H

#include "blockqueue.h"
#include <bits/types/FILE.h>
#include <cassert>
#include <memory>
#include <mutex>
#include <string>
#include <thread>

using namespace std;
class Log
{
public:
  //日志等级 日志路径 日志后缀 异步日志队列最大长度
  void init(int level, const char* path = "./log", const char* suffix = ".log",
            int maxQueueSize = 1024);
  static Log* instance();

private:
  Log();
  virtual ~Log();

private:
  int lineCount;   //线程默认数
  int today;       //时间
  bool isAsync;    //是否为异步
  FILE* fp;        //日志文件指针
  std::unique_ptr<BlockQueue<std::string>> que;
  std::unique_ptr<std::thread> writeThread;
  std::mutex mtx;
};
#endif