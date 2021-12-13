#include "write.h"
#include "query.h"
#include "pool.h"

#include <ctime>


int main() {
    // 创建写线程写入节点和边
    WriteThread wt;

    clock_t start, end;
    start = clock();
    wt.create_vertex_threads();
    //wt.create_edge_threads();
    end = clock();
    std::cout << "start: " << start << " end: " << end << " total: " << (double)(end - start)/CLOCKS_PER_SEC << std::endl;

    
    // 创建读线程读节点
    //QueryThread qt;
    //qt.create_query_num();
}