#include "write.h"
#include "pool.h"
#include "config.h"
#include <thread>
#include <sys/time.h>
#include <fstream>

std::string get_relation(int index) {
    if (index < 0 || index >= RELATIONS_NUMS) return "None";

    return relations[index];
}

int get_rand(int left, int right) {
    return (rand()%(right - left + 1)) + left;
}

/* 插入点的线程主函数：
 * 线程先从连接池 pool 取得一个session，再执行GQL插入；
 * 每个线程插入 n = config.h/VERTEX_NUM_PER_R 个节点，节点id为 tid * n + ( 0 -> n - 1)
 */
void write_vertex_main(ll tid) {
    // 连接nebula并进入space
    Pool& pool = Pool::get_instance();
    auto session = pool.get_session();
    session.execute("use "+ SPACE);   

    ll id_offset = tid * VERTEX_NUM_PER_W;

    for (int i = 0; i < VERTEX_NUM_PER_W; i += 500) {
        std::string gql;
        for (int k = 0; k < 500; k++) {
            std::string vid = "\"player" + std::to_string(id_offset + i + k) + "\" ";
            gql = gql + insert_person_prefix + vid + ":(" + vid + ");";
            // gql = gql + update_player_prefix + vid + " set name = \"change\"; ";
        }
        // std::string gql = update_player_prefix + vid + " set age = 20";

        // vid1 = "\"player" + std::to_string(id_offset + i) + "\"";
        // gql = gql + insert_person_prefix + vid + ":(" + vid + ", 18);";
	
	    auto result = session.execute(gql);
        if (result.errorCode != nebula::ErrorCode::SUCCEEDED) {
            std::cout << "Exit with error code: " << static_cast<int>(result.errorCode) << std::endl;
            std::cout << gql << std::endl;
        }

        if (i % 50000 == 0) {
            std::cout << "thread " << tid << " complete " << i << " update vertexes." << std::endl;
        }
    }

    session.release();
}

void WriteThread::create_vertex_threads() {
    std::thread threads[W_THREAD_NUM]; 

    struct timeval t1, t2;
    double timeuse;
    gettimeofday(&t1, nullptr);
    
    for (int i = 0; i < W_THREAD_NUM; i ++) {
        threads[i] = std::thread(write_vertex_main, i);
    }

    for (auto &thread : threads)
        thread.join();

    gettimeofday(&t2, nullptr);

    timeuse = (t2.tv_sec - t1.tv_sec) + (double)(t2.tv_usec - t1.tv_usec)/1000000.0;
    std::string file_name = "insert_test_time_5000,0000.txt";
    std::ofstream outfile(file_name);

    outfile << "Insert date 5000,0000 vertexes, time needed: " << timeuse << std::endl;
    
    std::cout << std::endl;
    std::cout << "All threads joined!" << std::endl;
    std::cout << "Insert 5000,0000 vertexes, time needed: " << timeuse << std::endl;

    
}

/* 插入边的线程主函数，每个线程插入 rand(总节点数 / 100, 总节点数 / 10) 条边：
 * 先随机得到需要插入的边的数量，再随机得到两个节点id，和节点间关系
 */
void write_edge_main(ll tid) {
    // 连接nebula并进入space
    Pool& pool = Pool::get_instance();
    auto session = pool.get_session();
    session.execute("use " + SPACE);

    int EDGE_NUM = get_rand(VERTEX_NUM/100, VERTEX_NUM/10);

    for (int i = 0; i < EDGE_NUM; i ++) {
        int from = get_rand(0, VERTEX_NUM - 1);
        int to;
        while ( (to = get_rand(0, VERTEX_NUM - 1)) == from);

        std::string val_relation = get_relation( get_rand(0, RELATIONS_NUMS - 1) );
	
	    std::string f = "\"player" + std::to_string(from) + "\"";
	    std::string t = "\"player" + std::to_string(to) + "\"";
        std::string gql = insert_p2p_prefix + f + "->" + t + ":(" + std::to_string(100) + ");";



        
	    //std::cout << gql << std::endl;
	    auto result = session.execute(gql);
        if (result.errorCode != nebula::ErrorCode::SUCCEEDED) {
            std::cout << "Exit with error code: " << static_cast<int>(result.errorCode) << std::endl;
            std::cout << gql << std::endl;
        }

        if (i % 100000 == 0) {
            std::cout << "thread " << tid << " complete " << i << " insert edge GQLs." << std::endl;
        }
    }
    
    session.release();
}

// 创建 W 个线程插入边
void WriteThread::create_edge_threads() {
    std::thread threads[W_THREAD_NUM]; 

    for (int i = 0; i < W_THREAD_NUM; i ++) {
        threads[i] = std::thread(write_edge_main, i);
    }

    for (auto &thread : threads)
        thread.join();
    std::cout << "All write threads joined!\n";
}