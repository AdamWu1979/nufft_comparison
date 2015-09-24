#ifndef BLOCKNUFFT3D_H
#define BLOCKNUFFT3D_H

#include "block3dspreader.h"

#define KERNEL_TYPE_GAUSSIAN		1
#define KERNEL_TYPE_KB				2
struct BlockNufft3DOptions {
	int N1,N2,N3; //uniform grid size
	int K1,K2,K3; //block size
	int M; //number of non-uniform points
	int num_threads; // The number of parallel threads to use
    double eps; //requested precision --> determines tau, oversamp factor and R
	int kernel_type;
};

//x,y,z should be in range [0,2pi)
Block3DSpreader *blocknufft3d_prepare(const BlockNufft3DOptions &opts,double *x,double *y,double *z);
bool blocknufft3d_run(Block3DSpreader *SS,const BlockNufft3DOptions &opts,double *uniform_d,double *nonuniform_d);
void test_blocknufft3d(BlockNufft3DOptions &opts);

/* MATLAB interface using MCWRAP
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
MCWRAP [ COMPLEX uniform_d[N1,N2,N3] ] = blocknufft3d( xyz[M,3], COMPLEX nonuniform_d[M,1], eps, N1, N2, N3, K1, K2, K3, num_threads, kernel_type )
    SET_INPUT M = size(xyz,1)
	SOURCES blocknufft3d.o qute.cpp besseli.cpp block3dspreader.o
    MEXARGS -largeArrayDims -lm -lgomp -lfftw3 -lfftw3_threads
IMPORTANT: In order to get openmp to work properly you must generate blocknufft3d.o separately using g++
  > g++ -fopenmp -c blocknufft3d.cpp block3dspreader.cpp -fPIC -O3
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
*/
void blocknufft3d(int N1,int N2,int N3,int M,double *uniform_d,double *xyz,double *nonuniform_d,double eps,int K1,int K2,int K3,int num_threads,int kernel_type);


#endif // BLOCKNUFFT3D_H
