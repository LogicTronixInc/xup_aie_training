/*
Copyright (C) 2023, Advanced Micro Devices, Inc. All rights reserved.
SPDX-License-Identifier: MIT
*/
#include <adf.h>
#include "graph.h"
#include <unistd.h>
#include <fstream>
using namespace adf;

mygraph gr;
// void ref_func(int32* din,int32 c[8],int32* dout,int size){
// 	static int32 d[8]={0,0,0,0,0,0,0,0};
// 	for(int i=0;i<size;i++){
// 		for(int j=0;j<7;j++){
// 			d[j]=d[j+1];
// 		}
// 		d[7]=*(din+i);
// 		int32 tmp=0;
// 		for(int j=0;j<8;j++){
// 			tmp+=d[j]*c[j];
// 		}
// 		*(dout+i)=tmp;
// 	}
// }
const int ITERATION=1;
const int BLOCK_SIZE_in_Bytes=ITERATION*256;
#if defined(__AIESIM__) || defined(__X86SIM__)
int main(int argc, char ** argv) {
    gr.init();

    int32* dinArray0=(int32*)GMIO::malloc(BLOCK_SIZE_in_Bytes);
    int32* dinArray1=(int32*)GMIO::malloc(BLOCK_SIZE_in_Bytes);
    int32* doutArray=(int32*)GMIO::malloc(BLOCK_SIZE_in_Bytes);
    int32* doutRef=(int32*)malloc(BLOCK_SIZE_in_Bytes);
    std::cout<<"GMIO::malloc completed"<<std::endl;

    int error=0;
    int32 coeff[8]={1,2,3,4,5,6,7,8};

    for(int i=0;i<ITERATION*256;i++){
	dinArray0[i]=i;
    }
    for(int i=0;i<ITERATION*256;i++){
	dinArray1[i]=i;
    }

    gr.gmioIn0.gm2aie_nb(dinArray0,BLOCK_SIZE_in_Bytes);
    gr.gmioIn1.gm2aie_nb(dinArray1,BLOCK_SIZE_in_Bytes);
    gr.run(ITERATION);
    gr.gmioOut.aie2gm_nb(doutArray,BLOCK_SIZE_in_Bytes);
    //PS can do other tasks here when data is transferring
    gr.gmioOut.wait();

    // ref_func(dinArray,coeff,doutRef,ITERATION*1024/4);
    // for(int i=0;i<ITERATION*1024/4;i++){
	// if(doutArray[i]!=doutRef[i]){
	// 	std::cout<<"ERROR:dout["<<i<<"]="<<doutArray[i]<<",gold="<<doutRef[i]<<std::endl;
	// 	error++;
	// }
    // }
    
    std::cout<<"GMIO transactions finished"<<std::endl;

    GMIO::free(dinArray0);
    GMIO::free(dinArray1);
    GMIO::free(doutArray);
 
    gr.end();
    // if(error==0){
	// 	std::cout<<"TEST PASSED!"<<std::endl;
    // }else{
	// 	std::cout<<"ERROR!"<<std::endl;
    // }

    return error;
};
#endif