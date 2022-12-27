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
# 项目展示
![01首页展示](https://user-images.githubusercontent.com/63970358/209692724-ea0d43d4-5b69-46a9-88f1-e4dccd4d4e4b.png)

![02图片测试](https://user-images.githubusercontent.com/63970358/209692741-dc636464-bfd4-4a99-9068-f9c91ca59aed.png)
![03注册展示](https://user-images.githubusercontent.com/63970358/209692751-85421773-018f-42d4-8b0d-e830e04fda5b.png)

![04视频测试](https://user-images.githubusercontent.com/63970358/209692763-b563f44d-fbaa-4e53-b5f1-d25ddea37356.png)
![05测试结果](https://user-images.githubusercontent.com/63970358/209692765-a6f43977-3c57-4e83-a29f-1322d195f457.png)
