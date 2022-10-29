/*
 * @Date: 2022-10-09 09:19:10
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-10-28 23:00:05
 * @FilePath: /VortexServer/code/log/log.h
 */
#ifndef LOG_H
#define LOG_H

#include <cassert>
class Log
{
public:
  //日志等级 日志路径 日志后缀 异步日志队列最大长度
  void init(int level, const char* path = "./log", const char* suffix = ".log",
            int maxQueueSize = 1024);
  static Log* getInstance();

private:
  Log();
  virtual ~Log();
};
#endif