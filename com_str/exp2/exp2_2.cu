#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "cuda.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>

#define MATRIX_SIZE 1000
#define BLOCK_SIZE 16
int DevicedChoosed = 0;

void printDeviceProp(const cudaDeviceProp& prop)
//��ӡ�豸��Ϣ
{
	printf("Device Name : %s.\n", prop.name);
	printf("totalGlobalMem : %d.\n", prop.totalGlobalMem);
	printf("sharedMemPerBlock : %d.\n", prop.sharedMemPerBlock);
	printf("regsPerBlock : %d.\n", prop.regsPerBlock);
	printf("warpSize : %d.\n", prop.warpSize);
	printf("memPitch : %d.\n", prop.memPitch);
	printf("maxThreadsPerBlock : %d.\n", prop.maxThreadsPerBlock);
	printf("maxThreadsDim[0 - 2] : %d %d %d.\n", prop.maxThreadsDim[0], prop.maxThreadsDim[1], prop.maxThreadsDim[2]);
	printf("maxGridSize[0 - 2] : %d %d %d.\n", prop.maxGridSize[0], prop.maxGridSize[1], prop.maxGridSize[2]);
	printf("totalConstMem : %d.\n", prop.totalConstMem);
	printf("major.minor : %d.%d.\n", prop.major, prop.minor);
	printf("clockRate : %d.\n", prop.clockRate);
	printf("textureAlignment : %d.\n", prop.textureAlignment);
	printf("deviceOverlap : %d.\n", prop.deviceOverlap);
	printf("multiProcessorCount : %d.\n", prop.multiProcessorCount);
}

//CUDA ��ʼ��
bool InitCUDA()
{
	int count;
	//ȡ��֧��Cuda��װ�õ���Ŀ
	cudaGetDeviceCount(&count);
	if (count == 0) {
		fprintf(stderr, "There is no device.\n");
		return false;
	}
	int i;
	for (i = 0; i < count; i++) {
		cudaDeviceProp prop;
		cudaGetDeviceProperties(&prop, i);
		//��ӡ�豸��Ϣ
		printDeviceProp(prop);
		if (cudaGetDeviceProperties(&prop, i) == cudaSuccess) {
			if (prop.major >= 1) {
				break;
			}
		}
	}

	if (i == count) {
		fprintf(stderr, "There is no device supporting CUDA 1.x.\n");
		return false;
	}
	cudaSetDevice(i);
	DevicedChoosed = i;
	return true;
}

void matMultCPU(const float* a, const float* b, float* c, int n)
//openmp���д���
{
	omp_set_num_threads(32);
	printf("Procs: %d, Thread: %d \n", omp_get_num_procs(), omp_get_max_threads());
#pragma omp parallel for
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			double t = 0;
			for (int k = 0; k < n; k++)
			{
				t += (double)a[i * n + k] * b[k * n + j];
			}
			c[i * n + j] = t;
		}
	}
}

//GPU���м������˷�
__global__ void matMultCUDAKernel1(const float* a, const float* b, float* c, int n)
{
	//������� thread Ӧ�ü���� row �� col
	const int col = blockIdx.x * blockDim.x + threadIdx.x;
	const int row = blockIdx.y * blockDim.y + threadIdx.y;

	int i;
	//�������˷� Kahan��s Summation Formula
	if (row < n && col < n)
	{
		float t = 0;
		float y = 0;
		for (i = 0; i < n; i++)
		{
			float r;

			y -= a[row * n + i] * b[i * n + col];
			r = t - y;
			y = (r - t) + y;
			t = r;
		}
		c[row * n + col] = t;
	}
}

void genMat(float* arr, int n)
//���ɾ���
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			arr[i * n + j] = (float)rand() / RAND_MAX + (float)rand() / (RAND_MAX * RAND_MAX);
		}
	}

}

typedef struct Error {
	float max;
	float average;
}Error;

Error accuracyCheck(const float* a, const float* b, int n)
{
	Error err;
	err.max = 0;
	err.average = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (b[i * n + j] != 0)
			{
				//fabs�󸡵���x�ľ���ֵ
				float delta = fabs((a[i * n + j] - b[i * n + j]) / b[i * n + j]);
				if (err.max < delta) err.max = delta;
				err.average += delta;
			}
		}
	}
	err.average = err.average / (n * n);
	return err;
}

static void matMultCPU_serial(const float* a, const float* b, float* c, int n)
//���м���ʱ��
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			double t = 0;
			for (int k = 0; k < n; k++)
			{
				t += (double)a[i * n + k] * b[k * n + j];
			}
			c[i * n + j] = t;
		}
	}
}

int main(int argc, char** argv)
{
	//CUDA ��ʼ��
	if (!InitCUDA()) return 0;
	cudaDeviceProp prop;
	cudaGetDeviceProperties(&prop, DevicedChoosed);
	//�������
	float* a, * b, * c, * d;
	int n = MATRIX_SIZE;
	if (argc >= 2) n = atoi(argv[1]) > 0 ? atoi(argv[1]) : MATRIX_SIZE;

	//����host�ڴ�
	cudaMallocHost((void**)&a, sizeof(float) * n * n);
	cudaMallocHost((void**)&b, sizeof(float) * n * n);
	cudaMallocHost((void**)&c, sizeof(float) * n * n);
	d = (float*)malloc(sizeof(float) * n * n);

	genMat(a, n);
	genMat(b, n);

	float* cuda_a, * cuda_b, * cuda_c;
	clock_t start, stop;
	//����GPU�ϵ��ڴ�
	cudaMalloc((void**)&cuda_a, sizeof(float) * n * n);
	cudaMalloc((void**)&cuda_b, sizeof(float) * n * n);
	cudaMalloc((void**)&cuda_c, sizeof(float) * n * n);

	//����������GPU�ڴ�
	cudaMemcpy(cuda_a, a, sizeof(float) * n * n, cudaMemcpyHostToDevice);
	cudaMemcpy(cuda_b, b, sizeof(float) * n * n, cudaMemcpyHostToDevice);
	start = clock();
	//���ú˺�������
	dim3 blockSize(BLOCK_SIZE, BLOCK_SIZE, 1);
	dim3 gridSize((n + BLOCK_SIZE - 1) / BLOCK_SIZE, (n + BLOCK_SIZE - 1) / BLOCK_SIZE, 1);//����ȡ��
	matMultCUDAKernel1 <<<gridSize, blockSize >>> (cuda_a, cuda_b, cuda_c, n);

	//���������ƻ����棬��ʽ����ͬ������
	cudaMemcpy(c, cuda_c, sizeof(float) * n * n, cudaMemcpyDeviceToHost);
	stop = clock();
	//�ͷ�GPU�ϵ��ڴ�
	cudaFree(cuda_a);
	cudaFree(cuda_b);
	cudaFree(cuda_c);
	//GPU memory
	printf("GPU memory: %e MB\n", (double)(n * n * 8) / (1024. * 1024.));
	//GPU time
	double gpu_t = ((double)stop - start) / CLOCKS_PER_SEC * 1000.0;
	printf("GPU time: %3f ms\n", gpu_t);
	//CPU time
	//start = clock();
	////matMultCPU(a, b, d, n);
	//matMultCPU_serial(a, b, c, n);
	//stop = clock();
	//double cpu_t = ((double)stop - start) / CLOCKS_PER_SEC * 1000.0;
	//printf("CPU_serial time: %3f ms\n", cpu_t);
	//printf("CUDA S0: %3f\n", cpu_t / gpu_t);

	//start = clock();
	//matMultCPU(a, b, d, n);
	//stop = clock();
	//double cpu2_t = ((double)stop - start) / CLOCKS_PER_SEC * 1000.0;
	//printf("CPU_parallel time: %3f ms\n", cpu2_t);
	//printf("OpenMP S0: %3f\n", cpu_t / cpu2_t);

	return 0;
}