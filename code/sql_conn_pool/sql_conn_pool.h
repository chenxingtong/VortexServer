/*
 * @Date: 2022-11-07 14:31:21
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-07 16:29:09
 * @FilePath: /VortexServer/code/sql_conn_pool/sql_conn_pool.h
 */
#ifndef SQL_CONN_POOL_H
#define SQL_CONN_POOL_H

#include "../lock/locker.h"
#include "../log/log.h"
#include <mutex>
#include <mysql/mysql.h>
#include <queue>
#include <semaphore.h>
#include <string>
#include <thread>
using namespace std;

class SqlConnPool
{
public:
  void init(const char* host, int port, const char* user, const char* pwd, const char* dbname,
            int maxConnCnt);
  void destory();   //析构函数调用
  static SqlConnPool* instance();

private:
  SqlConnPool();
  ~SqlConnPool();

  int useConnCnt;    //已使用连接数
  int freeConnCnt;   //空闲连接数

  queue<MYSQL*> connQue;
  mtx* mtxPool;
  sem* semFree;

public:
  MYSQL* getConn();
  void releaseConnection(MYSQL* conn);
  int getFreeConnection();
};

//总的封装
class SqlConnect
{
public:
  SqlConnect(MYSQL** psql, SqlConnPool* sqlConnPool);
  ~SqlConnect();

private:
  MYSQL* sql;
  SqlConnPool* sqlConnPool;
};
#endif