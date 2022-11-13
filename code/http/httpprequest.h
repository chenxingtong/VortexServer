/*
 * @Date: 2022-11-10 00:02:16
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-13 05:57:26
 * @FilePath: /VortexServer/code/http/httpprequest.h
 */
#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H
#include <cstddef>
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
const char CRLF[] = "\r\n";

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

public:
  HTTP_CODE parse(Buffer& buffer);   //总的解析函数

private:
  string method, path, version, body;
  bool linger;
  size_t contentLen;
  PARSE_STATE state;   //状态机对象state
  unordered_map<string, string> header;
  unordered_map<string, string> post;
  static const unordered_set<string> DEFAULT_HTML;
  static const unordered_map<string, int> DEFAULT_HTML_TAG;

private:
  //分析状态行
  HTTP_CODE parseRequestLine(const string& line);
  //分析头
  HTTP_CODE parseHeader(const string& line);
  HTTP_CODE parseBody(const string& line);
  void parsePath();   //分析行之解析地址
};
#endif