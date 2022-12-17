/*
 * @Date: 2022-11-07 14:31:21
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-12-08 08:02:20
 * @FilePath: /VortexServer/code/sqlconnpool/sql_conn_pool.h
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
  void init(const char* host, int port, const char* user, const char* pwd, const char* dbName,
            int maxConnCnt);

  void destroy();

  static SqlConnPool* instance();

  MYSQL* getConn();
  void releaseConn(MYSQL* conn);
  int getFreeConnCnt();

private:
  SqlConnPool();
  ~SqlConnPool();

  int useConnCnt;
  int freeConnCnt;

  queue<MYSQL*> connQue;
  mtx* mtxPool;
  sem* semFree;
};


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