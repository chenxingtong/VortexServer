/*
 * @Date: 2022-11-11 02:57:30
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-13 06:04:11
 * @FilePath: /VortexServer/code/http/httpprequest.cpp
 */
#include "httpprequest.h"
#include <algorithm>
#include <jsoncpp/json/value.h>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

const unordered_set<string> HttpRequest::DEFAULT_HTML{
    "/index", "/register", "/login", "/welcome", "/video", "/picture", "/upload", "/download"};

const unordered_map<string, int> HttpRequest::DEFAULT_HTML_TAG{{"/register.html", 0},
                                                               {"/login.html", 1}};

void HttpRequest::init()
{
  method = path = version = body = "";
  linger = false;
  contentLen = 0;
  state = REQUEST_LINE;
  header.clear();
  post.clear();
}

//总的解析函数
//把今后用到的\r\n直接const char CRLF[]代替
HTTP_CODE HttpRequest::parse(Buffer& buffer)
{
  while (buffer.readableBytes())
  {
    const char* lineEnd;
    string line;
    if (state != BODY)
    {
      // peek()函数起始位置+已读位置
      // beginwriteConst 起始位置+ 已写入位置
      // search函数  返回第一个字符串下标 失败返回
      // string()
      lineEnd = search(buffer.peek(), buffer.beginWriteConst(), CRLF, CRLF + 2);
      if (lineEnd == buffer.beginWrite()) return NO_REQUEST;
      line = string(buffer.peek(), lineEnd);
      buffer.retrieveUntil(lineEnd + 2);   //回收内存
    }
    else
    {
      //读取全部内容并清空缓存
      body += buffer.retrieveAllToStr();
      if (body.size() < contentLen)
      {
        return NO_REQUEST;
      }
    }
    switch (state)
    {
    case REQUEST_LINE:
    {
      HTTP_CODE ret = parseRequestLine(line);
      if (ret == BAD_REQUEST)
      {
        return BAD_REQUEST;
      }
      parsePath();
      break;
    }

    case HEADERS:
    {
    }
    case BODY:
    {
    }
    default: break;
    }
  }
  return NO_REQUEST;
}

void HttpRequest::parsePath()
{
  if (path == "/")
    path = "/index.html";
  else if (DEFAULT_HTML.count(path))   //如果存在path
    path += ".html";
  else if (path == "/list.json")
  {
    auto files : vector < string >= getFiles("./files");
  }
}
