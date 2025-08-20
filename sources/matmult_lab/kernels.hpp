#ifndef FUNCTION_KERNELS_H
#define FUNCTION_KERNELS_H

// void aie_vadd_stream(input_stream_int32 *in0, input_stream_int32 *in1, output_stream_int32 *out);
#include <adf.h>

using namespace adf;

void matrix_mul(input_buffer<int8> & __restrict matA, input_buffer<int8> & __restrict matB, output_buffer<int8> & __restrict matC);

#endif /**********__KERNELS_H__**********/