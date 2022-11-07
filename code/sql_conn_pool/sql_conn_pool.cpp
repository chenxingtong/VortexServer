/*
 * @Date: 2022-11-07 14:48:03
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-07 16:29:46
 * @FilePath: /VortexServer/code/sql_conn_pool/sql_conn_pool.cpp
 */
#include "sql_conn_pool.h"
#include <cassert>
#include <cstddef>
#include <mysql/mysql.h>
using namespace std;


SqlConnPool ::SqlConnPool()
{
  useConnCnt = 0;
  freeConnCnt = 0;
}

SqlConnPool* SqlConnPool::instance()
{
  static SqlConnPool connPool;
  return &connPool;
}

//重写init
void SqlConnPool::init(const char* host, int port, const char* user, const char* pwd,
                       const char* dbname, int maxConnCnt = 10)
{
  assert(maxConnCnt > 0);
  //在不断地鹅循环中
  for (int i = 0; i < maxConnCnt; i++)
  {
    MYSQL* sql = nullptr;
    sql = mysql_init(sql);
    //如果连接失败
    if (!sql)
    {
      LOG_ERROR("mysql init eror");
      assert(sql);
    }
    sql = mysql_real_connect(sql, host, user, pwd, dbname, port, nullptr, 0);
    if (!sql)
    {
      LOG_ERROR("mysql connect eror");
    }
    //将连接的东西放进queue里
    connQue.push(sql);
  }
  this->freeConnCnt = maxConnCnt;
  mtxPool = new mtx();
  semFree = new sem(maxConnCnt);
}
//析构函数的实现

void SqlConnPool::destory()
{
  this->mtxPool->lock();
  //关闭链接
  while (!connQue.empty())   //不为空
  {
    MYSQL* item = connQue.front();
    connQue.pop();
    mysql_close(item);
  }
  this->mtxPool->unlock();
  delete (mtxPool);
  delete (semFree);
  mysql_library_end();   //直接撤掉初始化环境，不用再设置useconn = 0；
}
SqlConnPool ::~SqlConnPool()
{
  this->destory();
}

MYSQL* SqlConnPool::getConn()
{
  MYSQL* sql = nullptr;
  this->semFree->wait();
  this->mtxPool->lock();
  sql = connQue.front();
  connQue.pop();
  this->useConnCnt++;
  this->freeConnCnt--;
  this->mtxPool->unlock();
  return sql;
}
SqlConnect::SqlConnect(MYSQL** psql, SqlConnPool* SqlConnPool)
{
  assert(SqlConnPool);
  //得到当前链接
  this->sql = SqlConnPool->getConn();
  *psql = this->sql;
  this->sqlConnPool = SqlConnPool;
}
void SqlConnPool::releaseConnection(MYSQL* sql)
{
  assert(sql);
  this->mtxPool->lock();
  connQue.push(sql);
  this->useConnCnt--;
  this->freeConnCnt++;
  this->mtxPool->unlock();
  this->semFree->post();
}
SqlConnect::~SqlConnect()
{
  if (this->sql)
  {
    this->sqlConnPool->releaseConnection(this->sql);
  }
}