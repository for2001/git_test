#include "config.h"


class Pool {
    public:
        static Pool& get_instance() {
            static Pool instance;
            return instance;
        }

        Pool() {
            pool.init({ADDR}, nebula::Config{});
        };
        ~Pool() {};

        nebula::Session get_session() {
            return pool.getSession(USER, PASSWD);
        }
    
    private:
        nebula::ConnectionPool pool;
        Pool(const Pool&) = delete;
        Pool& operator=(const Pool&) = delete;
};