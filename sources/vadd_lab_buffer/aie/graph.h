#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <adf.h>
#include "adf/new_frontend/adf.h"
#include "kernels.hpp"

class mygraph: public adf::graph
{
private:
	adf::kernel k_m;

public:
	adf::output_gmio gmioOut;
	adf::input_gmio gmioIn0;
    adf::input_gmio gmioIn1;

	mygraph(){
		k_m=adf::kernel::create(aie_vadd_buffer);
		gmioOut=adf::output_gmio::create("gmioOut",64,1000);
		gmioIn0=adf::input_gmio::create("gmioIn0",64,1000);
        gmioIn1=adf::input_gmio::create("gmioIn1",64,1000);

		adf::connect<>(gmioIn0.out[0], k_m.in[0]);
        adf::connect<>(gmioIn1.out[0], k_m.in[1]);
		adf::connect<>(k_m.out[0], gmioOut.in[0]);

        // dimensions(k_m.in[0]) = {2048};
        // dimensions(k_m.in[1]) = {2048};
        // dimensions(k_m.out[0]) = {2048};

		adf::source(k_m) = "vadd_buffer.cc";
		adf::runtime<adf::ratio>(k_m)= 0.9;
	};
};

#endif