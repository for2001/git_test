#include "query.h"

use std::string;
void query_num(ll tid, int& sync_val) {
    // 连接nebula并进入space
    Pool& pool = Pool::get_instance();
    auto session = pool.get_session();
    session.execute("use " + SPACE);

    // 日志
    //string file_name = "log_query_" + std::to_string(tid) + ".txt";
    //std::ofstream outfile(file_name);

    auto result = session.execute(query_num);
    if (result.errorCode != nebula::ErrorCode::SUCCEEDED) {
        std::cout << "Exit with error code: " << static_cast<int>(result.errorCode) << std::endl;
    }
    std::count << *result.data << std::endl;

        
    // 如果gql正常执行
    // outfile << "match (v:player) return count(v)" << std::endl;
    // outfile << *result.data << std::endl; 


    // outfile.close();
    session.release();
}

// 创建 R_THREAD_NUM 个线程读
void QueryThread::create_query_num() {
    std::thread threads[R_THREAD_NUM]; 

    for (int i = 0; i < R_THREAD_NUM; i ++) {
        threads[i] = thread(query_num, i);
    }

    for (auto &thread : threads)
        thread.join();
    std::cout << "All threads joined!\n";
}
