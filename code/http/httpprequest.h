/*
 * @Date: 2022-11-10 00:02:16
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-11 02:57:10
 * @FilePath: /VortexServer/code/http/httpprequest.h
 */
#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include <errno.h>
#include <jsoncpp/json/json.h>
#include <mysql/mysql.h>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "../buffer/buffer.h"
#include "../log/log.h"
#include "../sql_conn_pool/sql_conn_pool.h"
#include "../threadpool/threadpool.h"

using namespace std;

enum HTTP_CODE
{
  NO_REQUEST = 0,
  GET_REQUEST,
  BAD_REQUEST,
  NO_RESOURSE,
  FORBIDDENT_REQUEST,
  FILE_REQUEST,
  INTERNAL_ERROR,
  CLOSED_CONNECTION
};

enum PARSE_STATE
{
  REQUEST_LINE = 0,
  HEADERS,
  BODY,
  FINISH
};

class HttpRequest
{
public:
  HttpRequest() { init(); }
  ~HttpRequest() = default;
  void init();

private:
  string method, path, version, bidy;
};
#endif