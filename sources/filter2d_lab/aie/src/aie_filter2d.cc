#include "imgproc/xf_filter2d_16b_aie.hpp"
#include "kernel.h"

void filter2D(adf::input_buffer<int16>& input, const int16_t (&coeff)[16], adf::output_buffer<int16>& output) {
        xf::cv::aie::filter2D_k3_border(input, coeff, output);
};