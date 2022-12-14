/*
 * @Date: 2022-11-09 11:32:27
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-12-08 07:59:20
 * @FilePath: /VortexServer/code/http/httpresponse.h
 */
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unordered_map>

#include "../buffer/buffer.h"
#include "../log/log.h"

using namespace std;

class HttpResponse
{
public:
  HttpResponse();
  ~HttpResponse();

  void init(const string& srcDir, string& path, bool isKeepAlive = false, int code = -1);
  void makeResponse(Buffer& buffer);
  char* getFile();
  size_t getFileLen() const;
  void errorContent(Buffer& buffer, string message);
  int getCode() const;
  void unmapFile();

private:
  void addState(Buffer& buffer);
  void addHeader(Buffer& buffer);
  void addContent(Buffer& buffer);

  void errorHtml();
  string getFileType();

  int code;
  bool isKeepAlive;

  string path;
  string srcDir;

  char* mmFile;
  struct stat mmFileStat;

  static const unordered_map<string, string> SUFFIX_TYPE;
  static const unordered_map<int, string> CODE_STATUS;
  static const unordered_map<int, string> CODE_PATH;
};

#endif