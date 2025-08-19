#ifndef _KERNELS_16B_H_
#define _KERNELS_16B_H_

#include <adf/stream/types.h>
#include <adf/window/types.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "adf.h"
#include <adf/io_buffer/io_buffer.h>

#define PARALLEL_FACTOR_16b 16 // Parallelization factor for 16b operations (16x mults)
#define SRS_SHIFT 10           // SRS shift used can be increased if input data likewise adjusted)

void filter2D(adf::input_buffer<int16>& input, const int16_t (&coeff)[16], adf::output_buffer<int16>& output);

#endif