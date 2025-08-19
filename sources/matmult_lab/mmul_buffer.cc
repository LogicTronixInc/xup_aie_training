#include <aie_api/aie.hpp>
#include <aie_api/aie_adf.hpp>
#include <aie_api/utils.hpp>
using namespace adf;
const int SHIFT=10;

//For element mmul
const int M=4;
const int K=16;
const int N=8;

//Total matrix sizes
const int rowA=64;
const int colA=64;
const int colB=64;

//mmul numbers
const int num_rowA=rowA/M;
const int num_colA=colA/K;
const int num_colB=colB/N;

void matrix_mul(input_buffer<int8> & __restrict matA, input_buffer<int8> & __restrict matB, output_buffer<int8> & __restrict matC){
   using MMUL = aie::mmul<M, K, N, int8, int8>;

   const int8* __restrict pA=(int8*)matA.data();
   const int8* __restrict pB=(int8*)matB.data();
   int8* __restrict pC=(int8*)matC.data();
	//For profiling only 
	unsigned cycle_num[2];
	aie::tile tile=aie::tile::current();
	cycle_num[0]=tile.cycles();//cycle counter of the AI Engine tile

	for (unsigned i = 0; i < num_rowA; i++) {
       for (unsigned j = 0; j < num_colB; j++) chess_prepare_for_pipelining {
           const int8 * __restrict pA1 = pA + (      i * num_colA +       0) * MMUL::size_A;
           const int8 * __restrict pB1 = pB +  (      0 * num_colB +       j) * MMUL::size_B;
 
           aie::vector<int8, MMUL::size_A> A0 = aie::load_v<MMUL::size_A>(pA1); pA1 += MMUL::size_A;
           aie::vector<int8, MMUL::size_B> B0 = aie::load_v<MMUL::size_B>(pB1); pB1 += MMUL::size_B * num_colB;
 
           MMUL C00; C00.mul(A0, B0);
 
           for (unsigned k = 0; k < num_colA-1; k++) chess_flatten_loop {
               A0 = aie::load_v<MMUL::size_A>(pA1); pA1 += MMUL::size_A;
               B0 = aie::load_v<MMUL::size_B>(pB1); pB1 += MMUL::size_B * num_colB;
               C00.mac(A0, B0);
           }
 
           aie::store_v(pC, C00.template to_vector<int8>(SHIFT)); pC += MMUL::size_C;
       }
	}
	//For profiling only 	
	cycle_num[1]=tile.cycles();//cycle counter of the AI Engine tile
	printf("start=%d,end=%d,total=%d\n",cycle_num[0],cycle_num[1],cycle_num[1]-cycle_num[0]);

}