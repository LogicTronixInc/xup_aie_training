#ifndef __KERNEL_H__
#define __KERNEL_H__
#include <adf.h>
using namespace adf;
    void aie_vadd_buffer(input_buffer<int32, extents<256>> & restrict in0, input_buffer<int32, extents<256>> & restrict in1, output_buffer<int32, extents<256>> & restrict out);
#endif