//
// Copyright (C) 2023, Advanced Micro Devices, Inc. All rights reserved.
// SPDX-License-Identifier: MIT
//


#ifndef _NNDCT_BATCHNORM_KERNELS_H_
#define _NNDCT_BATCHNORM_KERNELS_H_


#ifdef __cplusplus
extern "C"{
#endif 
void cudaF_batch_norm_inference(int row,int col,float eps,
  const float* input,const float* gamma,const float* beta,
  const float* mean,const float* var,float* out);

void cuda_batch_norm_training(int row,int col,float eps,
  int renorm,const float* input,const float* gamma,
  const float* beta,const float* mean,const float* var,float* out);

void cudaF_batch_norm_scan(int row,int col,float eps,
  const float* input,const float* gamma,const float* beta,
  const float* mean,const float* var,float* out,float* max,float* min);

void cudaF_batch_norm_quant(int row,int col,float eps,
  const float* input,const float* gamma,const float* beta,
  const float* mean,const float* var,float* out,
  const int parammaxA,const int parammaxB,
  const float paramampA,const float paramampB,
  const int in_max,const float in_amp, int keep_scale);

void cudaF_batch_norm_back_ivar(int row,int col,
  const float* out_grad,const float* input,const float* mean,
  const float* gamma,float* grad_buff);

void cudaF_batch_norm_back(int row,int col,float eps,int renorm,
  const float* out_grad,const float* input,const float* gamma,
  const float* mean,const float* var,const float* divar,
  float* in_grad,float* grad_buff);
#ifdef __cplusplus
} //extern "C"
#endif

#endif //_NNDCT_BATCHNORM_KERNELS_H_
