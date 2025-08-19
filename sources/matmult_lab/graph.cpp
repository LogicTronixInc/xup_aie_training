#include "graph.hpp"

SimpleGraph gr;

int main(int argc, char ** argv) {
	int iterations=100;
	int total_bytes=iterations*64*64;
#ifdef __AIESIM__
	event::handle handle = event::start_profiling(gr.in0, event::io_stream_start_to_bytes_transferred_cycles, total_bytes);
	if(handle==event::invalid_handle){    
		printf("ERROR:Invalid handle. Only two performance counter in a AIE-PL interface tile\n");    
		return 1;
	} 
#endif
	gr.init();
	gr.run(iterations);
	gr.wait();
#ifdef __AIESIM__
	long long count = event::read_profiling(handle); 
	event::stop_profiling(handle); 
	std::cout<<"Cycles per iter="<<count/iterations<<std::endl;
#endif
	return 0;
}