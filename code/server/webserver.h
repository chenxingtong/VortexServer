/*
 * @Date: 2022-11-15 01:18:59
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-11-15 01:19:09
 * @FilePath: /VortexServer/code/server/webserver.h
 */
#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <arpa/inet.h>
#include <assert.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <unordered_map>

#include "../http/httpconnect.h"
#include "../log/log.h"
#include "../sql_conn_pool/sql_conn_pool.h"
#include "../threadpool/threadpool.h"
#include "epoller.h"
//#include "../timer/heaptimer.h"
#endif