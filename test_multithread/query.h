#ifndef C_QUERY_H_
#define C_QUERY_H_

const std::string query_num = "match (v:player) return count(v)";
const std::string p2p_prefix = "fetch prop on player";

class QueryThread {
private:
    
public:
    void create_query_num();
};

#endif