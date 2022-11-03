/*
 * @Date: 2022-10-28 22:52:41
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-03 16:10:03
 * @FilePath: /VortexServer/code/log/log.cpp
 */

/*异步日志是把执行线程放进阻塞队列中的，再用专门的线程去向文件写日志
记得上锁*/

#include "log.h"

using namespace std;

Log::Log()
{
  lineCount = 0;
  isAsync = false;
  writeThread = nullptr;
  que = nullptr;
  today = 0;
  fp = nullptr;
}

Log::~Log()
{
  /*析构函数要关闭资源，但是一定要确定缓存写入指针后*/
  if (writeThread && writeThread->joinable())
  {
    while (!que->empty())
    {
      que->flush();
    };
    que->close();
    //回收写入线程的资源
    writeThread->join();
  }
  //缓存写入文件后再关闭指针
  if (fp)
  {
    lock_guard<mutex> locker(mtx);
    // flush();日志函数，将缓存文件写入文件中。
    fclose(fp);
  }
}
/* 单例模式唯一实例 */
Log* Log::instance()
{
  static Log obj;
  return &obj;
}
void Log::init(int level = 1, const char* path, const char* suffix, int maxQueueSize) {}









/*
log(很多参数在这里初始化)
~log(关闭资源-》确定缓存写入指针后);
日志等级函数
设置日志等级函数

初始化：日志等级 = 1，路径默认为XXX，日志后缀为.log，最大队列长度为1024

1. 初始化且初始化阻塞队列，其中 如果阻塞队列==0 =》阻塞队列接管新队列 且写入线程接管新线程
否则不开启异步

2. 写日志功能

3.
4. linecount为0
5. 初始化很多文件名
6. 初始化文件指针
7. 写日志
8. 添加日志等级信息
9. 将缓存数据写入文件的flush函数
10.异步写日志之
*/