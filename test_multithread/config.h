#ifndef C_CONFIG_H_
#define C_CONFIG_H_

#include <iostream>
#include <string>
#include <thread>
#include <mutex>

#include <nebula/client/Config.h>
#include <nebula/client/ConnectionPool.h>
#include <nebula/client/Init.h>


typedef long long ll;


// graph service's ip:port
const std::string ADDR = "127.0.0.1:9669";
// 并发写线程数
const int W_THREAD_NUM = 10;
// 并发读线程数
const int R_THREAD_NUM = 10;
// 节点总数
const int VERTEX_NUM = 50000000;
// 每个读线程负责的处理的节点数
const int VERTEX_NUM_PER_R = VERTEX_NUM / R_THREAD_NUM;
// 每个写线程负责处理的节点数
const int VERTEX_NUM_PER_W = VERTEX_NUM / W_THREAD_NUM;
// 操作的图空间
const std::string SPACE = "my_space0";
// 登录nebula的用户名和密码
const std::string USER = "root";
const std::string PASSWD = "123";

#endif


/*
space schema:
create space test(vid_type=int64)
person(name string)
*/