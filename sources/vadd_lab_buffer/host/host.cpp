#include <adf.h>
#include <unistd.h>
#include <fstream>
#include "xrt/xrt_kernel.h"
#include "xrt/xrt_graph.h"
#include "xrt/xrt_aie.h"

using namespace adf;



const int ITERATION=1;
const int BLOCK_SIZE_in_Bytes=ITERATION*256;

int main(int argc, char ** argv) {
    // Create XRT device handle for ADF API
    char* xclbinFilename = argv[1];
	// Open xclbin
	auto device = xrt::device(0); //device index=0
	auto uuid = device.load_xclbin(xclbinFilename);

	auto din0_buffer = xrt::aie::bo (device, BLOCK_SIZE_in_Bytes,xrt::bo::flags::normal, /*memory group*/0); //Only non-cacheable buffer is supported
	int* din0Array= din0_buffer.map<int*>();
    auto din1_buffer = xrt::aie::bo (device, BLOCK_SIZE_in_Bytes,xrt::bo::flags::normal, /*memory group*/0); //Only non-cacheable buffer is supported
	int* din1Array= din1_buffer.map<int*>();
	auto dout_buffer = xrt::aie::bo (device, BLOCK_SIZE_in_Bytes,xrt::bo::flags::normal, /*memory group*/0); //Only non-cacheable buffer is supported
	int* doutArray= dout_buffer.map<int*>();
    
    std::cout<<"GMIO::malloc completed"<<std::endl;

    for(int i=0;i<ITERATION*256;i++){
		din0Array[i]=i;
    }

    for(int i=0;i<ITERATION*256;i++){
		din1Array[i]=i;
    }

	auto ghdl=xrt::graph(device,uuid,"gr");
	din0_buffer.async("gr.gmioIn0",XCL_BO_SYNC_BO_GMIO_TO_AIE,BLOCK_SIZE_in_Bytes,/*offset*/0);
    din1_buffer.async("gr.gmioIn1",XCL_BO_SYNC_BO_GMIO_TO_AIE,BLOCK_SIZE_in_Bytes,/*offset*/0);
    ghdl.run(ITERATION);
	auto dout_buffer_run=dout_buffer.async("gr.gmioOut",XCL_BO_SYNC_BO_AIE_TO_GMIO,BLOCK_SIZE_in_Bytes,/*offset*/0);
    //PS can do other tasks here when data is transferring
    dout_buffer_run.wait();//Wait for gmioOut to complete

      
    std::cout<<"GMIO transactions finished"<<std::endl;

	ghdl.end();

}
