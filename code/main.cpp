/*
 * @Date: 2022-10-03 16:50:37
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-12-08 07:34:25
 * @FilePath: /VortexServer/code/main.cpp
 */
#include "../code/server/webserver.h"
#include <unistd.h>

/*
响应模式
    0：连接和监听都是LT
    1：连接ET，监听LT
    2：连接LT，监听ET
    3：连接和监听都是ET
日志等级
    0：DEBUG
    1：INFO
    2：WARN
    3：ERROR
*/
int main()
{
  WebServer server(
      9006,
      3,
      60000,
      false,   // 客户端监听端口， ET触发模式， 连接计时1分钟， 优雅退出
      3306,
      "zhangsan",
      "123456",
      "webdb",   // 数据库相关，数据库监听端口，用户名，密码，数据库名
      12,
      6,
      10000,
      true,
      1,
      1024);   // 数据库连接池数量，线程池数量，最大连接数，日志开关，日志等级，日志异步队列容量
  server.start();
}