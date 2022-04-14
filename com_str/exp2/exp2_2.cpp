//#include <omp.h> 
//#include <stdio.h> 
//#include <stdlib.h>
//#include <math.h>
//#include <time.h>
//
//typedef struct Error {
//	float max;
//	float average;
//}Error;
//
//static void matMultCPU_serial(const float*, const float*, float*, int);
//static void matMultCPU_parallel(const float*, const float*, float*, int);
//void genMat(float*, int);
//Error accuracyCheck(const float*, const float*, int);
//
//int main(int argc, char** argv)
//{
//	/// test omp ///
//	omp_set_num_threads(512);
//	printf("Procs: %d, Thread: %d \n", omp_get_num_procs(), omp_get_max_threads());
////#pragma omp parallel for
//	//for (int i = 0; i < 10; i++)
//	//{
//	//	printf("Hello World %d from thread = %d\n", i, omp_get_thread_num());
//	//}
//	//基本情况
//	// Init matrix
//	float* a, * b, * c, * d;
//	int n = 1000;
//	if (argc == 2) n = atoi(argv[1]);
//	a = (float*)malloc(sizeof(float) * n * n);
//	b = (float*)malloc(sizeof(float) * n * n);
//	c = (float*)malloc(sizeof(float) * n * n);
//	d = (float*)malloc(sizeof(float) * n * n);
//
//	genMat(a, n);
//	genMat(b, n);
//
//	clock_t start, stop;
//	start = clock();
//	//串行计算
//
//	matMultCPU_serial(a, b, c, n);
//
//	stop = clock();
//	double serial = ((double)stop - start) / CLOCKS_PER_SEC * 1000.0;
//	printf("CPU Serial time: %3f ms\n", serial);//串行时间
//
//	start = clock();
//	//并行计算
//
//	matMultCPU_parallel(a, b, d, n);
//
//	stop = clock();
//	double parallel = ((double)stop - start) / CLOCKS_PER_SEC * 1000.0;
//	printf("CPU Parallel time: %3f ms\n", parallel);//并行时间
//	printf("S0: %3f\n", serial / parallel);
//	return 0;
//}
//
//static void matMultCPU_serial(const float* a, const float* b, float* c, int n)
////串行计算时间
//{
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			double t = 0;
//			for (int k = 0; k < n; k++)
//			{
//				t += (double)a[i * n + k] * b[k * n + j];
//			}
//			c[i * n + j] = t;
//		}
//	}
//}
//
//static void matMultCPU_parallel(const float* a, const float* b, float* c, int n)
////并行计算时间
//{
//	//int chunk = 100;
////#pragma omp parallel for schedule(static,chunk)
//#pragma omp parallel for schedule(dynamic)
////动态调度迭代的分配是依赖于运行状态进行动态确定的，所以哪个线程上将会运行哪些迭代是无法像静态一样事先预料的。对于dynamic，没有size参数的情况下，每个线程按先执行完先分配的方式执行1次循环
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			double t = 0;
//			for (int k = 0; k < n; k++)
//			{
//				t += (double)a[i * n + k] * b[k * n + j];
//			}
//			c[i * n + j] = t;
//		}
//	}
//}
//
//
//void genMat(float* arr, int n)
////随机生成矩阵
//{
//	int i, j;
//
//	for (i = 0; i < n; i++)
//	{
//		for (j = 0; j < n; j++)
//		{
//			arr[i * n + j] = (float)rand() / RAND_MAX + (float)rand() / (RAND_MAX * RAND_MAX);
//		}
//	}
//}
//
//
//Error accuracyCheck(const float* a, const float* b, int n)
//{
//	Error err;
//	err.max = 0;
//	err.average = 0;
//	for (int i = 0; i < n; i++)
//	{
//		for (int j = 0; j < n; j++)
//		{
//			if (b[i * n + j] != 0)
//			{
//				//fabs求浮点数x的绝对值
//				float delta = fabs((a[i * n + j] - b[i * n + j]) / b[i * n + j]);
//				if (err.max < delta) err.max = delta;
//				err.average += delta;
//			}
//		}
//	}
//	err.average = err.average / (n * n);
//	return err;
//}