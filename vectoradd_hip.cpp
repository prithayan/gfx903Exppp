/*
Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include <assert.h>
#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include<iostream>
#include "hip/hip_runtime.h"


#define HIP_ASSERT(x) (assert((x)==hipSuccess))


#define WIDTH     (4096*32)
#define HEIGHT    (4096)

#define NUM       (WIDTH*HEIGHT)

#define THREADS_PER_BLOCK_X  16
#define THREADS_PER_BLOCK_Y  16
#define THREADS_PER_BLOCK_Z  1


__device__ __forceinline__  uint rand_gen ( uint h )
{
  h += 1;
  h ^= h >> 16;
  h *= 0x85ebca6b;
  h ^= h >> 13;
  h *= 0xc2b2ae35;
  h ^= h >> 16;
  return h;
}
__global__ void 
vectoradd_float(float* __restrict__ a, const float* __restrict__ b, const float* __restrict__ c, int width, int height) 

  {
 
      int x = hipBlockDim_x * hipBlockIdx_x + hipThreadIdx_x;
      int y = hipBlockDim_y * hipBlockIdx_y + hipThreadIdx_y;

      float sum = 0 ;
      int i = (y * width + x);
      /*//if (i+20 *hipBlockDim_x> (width * height))
      //  return;
      float temp1 = b[(i+0)];
      float temp2 = b[(i+1*hipBlockDim_x)%(width * height)];
      float temp3 = b[(i+2*hipBlockDim_x)%(width * height)];
      float temp4 = b[(i+3*hipBlockDim_x)%(width * height)];
      float temp5 = b[(i+4*hipBlockDim_x)%(width * height)];
      float temp6 = b[(i+5*hipBlockDim_x)%(width * height)];
      float temp7 = b[(i+6*hipBlockDim_x)%(width * height)];
      float temp8 = b[(i+7*hipBlockDim_x)%(width * height)];
      float temp9 = b[(i+8*hipBlockDim_x)%(width * height)];
      float temp10= b[(i+9*hipBlockDim_x)%(width * height)];
      float temp12= b[(i+10*hipBlockDim_x)%(width * height)];
      float temp13= b[(i+11*hipBlockDim_x)%(width * height)];
      float temp14= b[(i+12*hipBlockDim_x)%(width * height)];
      float temp15= b[(i+13*hipBlockDim_x)%(width * height)];
      float temp16 = b[(i+14*hipBlockDim_x)%(width * height)];
      float temp17 = b[(i+15*hipBlockDim_x)%(width * height)];
      float temp18 = b[(i+16*hipBlockDim_x)%(width * height)];
      float temp19 = b[(i+17*hipBlockDim_x)%(width * height)];
      float temp20 = b[(i+18*hipBlockDim_x)%(width * height)];
      float temp21 = b[(i+19*hipBlockDim_x)%(width * height)];
      float Stemp1 =c[(0*hipBlockDim_x)];
      float Stemp2 =c[(1*hipBlockDim_x)];
      float Stemp3 =c[(2*hipBlockDim_x)];
      float Stemp4 =c[(3*hipBlockDim_x)];
      float Stemp5 =c[(4*hipBlockDim_x)];
      float Stemp6 =c[(5*hipBlockDim_x)];
      float Stemp7 =c[(6*hipBlockDim_x)];
      float Stemp8 =c[(7*hipBlockDim_x)];
      float Stemp9 =c[(8*hipBlockDim_x)];
      float Stemp10=c[(9*hipBlockDim_x)];
      float Stemp12=c[(10*hipBlockDim_x)];
      float Stemp13=c[(11*hipBlockDim_x)];
      float Stemp14=c[(12*hipBlockDim_x)];
      float Stemp15=c[(13*hipBlockDim_x)];
      float Stemp16 =c[(14*hipBlockDim_x)];
      float Stemp17 =c[(15*hipBlockDim_x)];
      float Stemp18 =c[(16*hipBlockDim_x)];
      float Stemp19 =c[(17*hipBlockDim_x)];
      float Stemp20 =c[(18*hipBlockDim_x)];
      float Stemp21 =c[(19*hipBlockDim_x)];
      sum = temp1*Stemp1 + temp2*Stemp2 + temp3*Stemp3 + temp4*Stemp4 +temp5*Stemp5 + temp6*Stemp6 + temp7*Stemp7 + temp8*Stemp8 + temp9*Stemp9 + temp10*Stemp10+ temp12*Stemp12 + temp13*Stemp13 + temp14*Stemp14 + temp15*Stemp15 + temp16*Stemp16  +temp17*Stemp17 + temp18*Stemp18 + temp19*Stemp19  + temp20*Stemp20 +  temp21*Stemp21;*/
#pragma unroll  10
      for (int index = 0 ; index < 20 ; index += hipBlockDim_x ){
        sum += b[rand_gen(i+index)] * c[(index)];
      }
     a[i] = sum ;


  }

#if 0
__kernel__ void vectoradd_float(float* a, const float* b, const float* c, int width, int height) {

  
  int x = blockDimX * blockIdx.x + threadIdx.x;
  int y = blockDimY * blockIdy.y + threadIdx.y;

  int i = y * width + x;
  if ( i < (width * height)) {
    a[i] = b[i] + c[i];
  }
}
#endif

using namespace std;

int main() {
  
  float* hostA;
  float* hostB;
  float* hostC;

  float* deviceA;
  float* deviceB;
  float* deviceC;

  hipDeviceProp_t devProp;
  hipGetDeviceProperties(&devProp, 0);
  cout << " System minor " << devProp.minor << endl;
  cout << " System major " << devProp.major << endl;
  cout << " agent prop name " << devProp.name << endl;



  cout << "hip Device prop succeeded " << endl ;


  int i;
  int errors;

  hostA = (float*)malloc(NUM * sizeof(float));
  hostB = (float*)malloc(NUM * sizeof(float));
  hostC = (float*)malloc(NUM * sizeof(float));
  
  // initialize the input data
  for (i = 0; i < NUM; i++) {
    hostB[i] = (float)i;
    hostC[i] = (float)i*100.0f;
  }
  
  HIP_ASSERT(hipMalloc((void**)&deviceA, NUM * sizeof(float)));
  HIP_ASSERT(hipMalloc((void**)&deviceB, NUM * sizeof(float)));
  HIP_ASSERT(hipMalloc((void**)&deviceC, NUM * sizeof(float)));
  
  HIP_ASSERT(hipMemcpy(deviceB, hostB, NUM*sizeof(float), hipMemcpyHostToDevice));
  HIP_ASSERT(hipMemcpy(deviceC, hostC, NUM*sizeof(float), hipMemcpyHostToDevice));


  hipLaunchKernelGGL(vectoradd_float, 
                  dim3(WIDTH/THREADS_PER_BLOCK_X, HEIGHT/THREADS_PER_BLOCK_Y),
                  dim3(THREADS_PER_BLOCK_X, THREADS_PER_BLOCK_Y),
                  0, 0,
                  deviceA ,deviceB ,deviceC ,WIDTH ,HEIGHT);


  HIP_ASSERT(hipMemcpy(hostA, deviceA, NUM*sizeof(float), hipMemcpyDeviceToHost));

  // verify the results
  errors = 0;
  for (i = 0; i < NUM; i++) {
    if (hostA[i] != (hostB[i] + hostC[i])) {
      errors++;
    }
  }
  if (errors!=0) {
    printf("FAILED: %d errors\n",errors);
  } else {
      printf ("PASSED!\n");
  }

  HIP_ASSERT(hipFree(deviceA));
  HIP_ASSERT(hipFree(deviceB));
  HIP_ASSERT(hipFree(deviceC));

  free(hostA);
  free(hostB);
  free(hostC);

  //hipResetDefaultAccelerator();

  return errors;
}
