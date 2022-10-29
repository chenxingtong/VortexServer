/*
 * @Date: 2022-10-28 22:52:41
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-10-29 05:28:34
 * @FilePath: /VortexServer/code/log/log.cpp
 */

/*异步日志是把执行线程放进阻塞队列中的，再用专门的线程去向文件写日志
记得上锁*/

#include "log.h"

using namespace std;

Log::Log() {}

Log::~Log()
{
  /*析构函数要关闭资源，但是一定要确定缓存写入指针后*/
}

void Log::init(int level = 1, const char* path, const char* suffix, int maxQueueSize) {}

/*
log(很多参数在这里初始化)
~log(关闭资源-》确定缓存写入指针后);
日志等级函数
设置日志等级函数

初始化：日志等级= 1，路径默认为XXX，日志后缀为.log，最大队列长度为1024

1. 参数对应
2. 开启异步
3. 如果阻塞队列==0 =》阻塞队列接管新队列 且写入线程接管新线程
否则不开启异步
4. linecount为0
5.初始化文件名



*/