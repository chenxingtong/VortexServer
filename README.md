# VortexServer
* 本项目是以游双《linux高性能服务器编程》和非常优秀的项目TinyWebServer为基础，经过多次优化调试的高并发服务器。
* 代码进一步简洁，删除了冗余和废弃的思路注释，保留了适当的注释，添加了部分知识点作为补充。适合有一定基础的新手学习。
## 项目介绍
* 利用Epoll与线程池实现Reactor高并发模型
* 利用状态机HTTP请求报文解析，可同时处理GET与POST请求
* 缓存优化：用vector容器封装char，实现了一个可自动扩容的缓冲区
* 基于epoll_wait实现定时功能，关闭超时的非活动连接
* 利用单例模式实现线程池，减少了线程创建与销毁的开销
* 访问服务器数据库实现web端用户注册、登录功能，可以请求服务器图片和视频文件
* 利用单例模式实现连接MySQL的数据库连接池，减少数据库连接建立与关闭的开销，实现了用户注册登录功能
优化：
* 定时器优化：将升序链表替换为小根堆实现的定时器，更简洁，效率更高。
* 读写函数优化：用正则表达式替换了传统的\r\n的替换，减少逻辑负担。
* 异步日志系统优化：利用单例模式与阻塞队列实现的异步日志系统。
* 其他优化：用了智能指针对锁的实现，日志等实现做出优化。
* 用vector代替部分链表，优化缓存和epoll的实现。
* 以上所有功能的实现再封装优化，使得逻辑更简洁。
## 项目展示
### 首页展示
![001](https://user-images.githubusercontent.com/63970358/209744714-2a54cb48-5d57-4b42-81ae-d4b65da8797b.png)
### 图片展示
![002](https://user-images.githubusercontent.com/63970358/209744728-cec3272e-c882-459d-b847-89e974bd8c09.png)
### 注册展示
![003](https://user-images.githubusercontent.com/63970358/209744739-317c84d0-43fa-485a-8af0-c3a457826ca5.png)
### 视频展示
![04视频测试](https://user-images.githubusercontent.com/63970358/209744752-352a78ee-b63b-419e-b9ba-58ac9aadca20.png)
### 并发测试
![05测试结果](https://user-images.githubusercontent.com/63970358/209744784-68a565c9-c548-4f0f-b804-bfdb8d18c926.png)
## 项目启动
下载分支
```
git@github.com:chenxingtong/VortexServer.git
```
配置数据库
```
//创建数据库
create database webdb;
//创建user表
USE webdb;
CREATE TABLE user(
    username char(50) NULL,
    passwd char(50) NULL
)ENGINE=InnoDB;
//添加数据
INSERT INTO user(username, passwd) VALUES('your name', 'your password');

//webdb是数据库名，user是表名，需要在main函数中传入
```
编译
```
make
./bin/VortexServer
```
浏览器访问
```
127.0.0.1:9006
#9006是在main函数中传入的服务器监听端口
```
## 压力测试
```
cd webbench-1.5 && make
./webbench-1.5/webbench -c 1000 -t 5 http://ip:port/
#测试结果如上图
```
## 致谢
《Linux高性能服务器编程》，游双著
TinWebServer————https://github.com/qinguoyi/TinyWebServer

