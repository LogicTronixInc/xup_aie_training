#include <adf.h>
#include "aie_api/aie.hpp"
#include <aie_api/utils.hpp>

void aie_vadd_stream(input_stream_int32 *in0, input_stream_int32 *in1, output_stream_int32 *out){
    aie::vector<int32, 4> a = readincr_v4(in0);
    aie::vector<int32, 4> b = readincr_v4(in1);
    aie::vector<int32, 4> res = aie::add(a, b);
    aie::print(a,true, "a =" );
    aie::print(b,true, "b =" );
    aie::print(res, true, "out =" );
    writeincr_v4(out, res);
    
}