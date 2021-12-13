#ifndef C_WRITE_H_
#define C_WRITE_H_

#include "config.h"

// p2p边的关系的取值范围
const std::string RECOGNIZE = "recognize";
const std::string FRIEND = "friend";
const std::string FAMILY = "family";

const int RELATIONS_NUMS = 3;
const std::string relations[] = {RECOGNIZE, FRIEND, FAMILY};

// GQL
const std::string insert_person_prefix = "insert vertex if not exists player(name) values ";
const std::string insert_p2p_prefix = "insert edge follow(degree) values ";
const std::string update_player_prefix = "update vertex on player ";


class WriteThread {
private:

public:
    // 创建若干线程插入边
    void create_edge_threads();
    // 创建若干线程插入节点
    void create_vertex_threads();
};

#endif
