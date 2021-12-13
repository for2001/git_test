Run : Multithread_test.o pool.h config.h write.o
	g++ -std=c++11 Multithread_test.o write.o pool.h config.h -I/usr/local/nebula/include -lnebula_graph_client -lpthread -o Run

Multithread_test.o : Multithread_test.cpp write.h pool.h config.h
	g++ -std=c++11 -c Multithread_test.cpp write.h pool.h config.h -I/usr/local/nebula/include -lnebula_graph_client -lpthread

write.o : write.cpp config.h write.h pool.h
	g++ -std=c++11 -c write.cpp config.h write.h pool.h -I/usr/local/nebula/include -lnebula_graph_client -lpthread
	 

.PHONY : clean
clean : 
	rm *.o
