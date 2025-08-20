#ifndef GRAPH_MODULE_H
#define GRAPH_MODULE_H

#include "kernels.hpp"
#include <adf.h>

using namespace adf;

class SimpleGraph : public adf::graph {

public :
  output_plio out;
  input_plio in0,in1;
private:
  adf::kernel k;

public:
  SimpleGraph() {
	out=output_plio::create("Dataout0", plio_64_bits,  "data/output0.txt");
	in0=input_plio::create("Datain0", plio_64_bits,  "data/matA.txt");
	in1=input_plio::create("Datain1", plio_64_bits,  "data/matB.txt");

	k = adf::kernel::create(matrix_mul);
    	adf::connect(in0.out[0], k.in[0]);
    	adf::connect(in1.out[0], k.in[1]);
    	adf::connect(k.out[0], out.in[0]);

	adf::source(k) = "mmul_buffer.cc";
	runtime<ratio>(k) = 0.9;

	adf::dimensions(k.in[0])={4096};
	adf::dimensions(k.in[1])={4096};
	adf::dimensions(k.out[0])={4096};
	
  }
};

#endif