/*
 * @Date: 2022-10-09 09:19:10
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-10-09 09:50:46
 * @FilePath: /VortexServer/code/log/log.h
 */
#ifndef LOG_H
#define LOG_H

class Log {
 public:
  void init(int level, const char* path = "./log", const char* suffix = ".log",
            int maxQueueCapacity = 1024);
  static Log* getInstance();

 private:
  Log();
  virtual ~Log();
};
#endif