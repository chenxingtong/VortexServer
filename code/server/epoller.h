/*
 * @Date: 2022-11-15 00:51:22
 * @LastEditors: chenxingtong 1244017825@qq.com
 * @LastEditTime: 2022-12-08 08:01:32
 * @FilePath: /VortexServer/code/server/epoller.h
 */
#ifndef EPOLLER_H
#define EPOLLER_H

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>

using namespace std;

class Epoller
{
public:
  explicit Epoller(int maxEvent = 1024);
  ~Epoller();

  bool addfd(int fd, uint32_t events);
  bool modfd(int fd, uint32_t events);
  bool delfd(int fd);

  int wait(int timeoutsMs = -1);

  int getEventfd(size_t i) const;
  uint32_t getEvents(size_t i) const;

private:
  int epollfd;

  vector<struct epoll_event> events;
};

#endif