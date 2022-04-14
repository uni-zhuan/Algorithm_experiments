//#include <omp.h> 
//#include <stdio.h> 
//#include <stdlib.h>
//#include <math.h>
//#include <time.h>
//static long num_steps = 10000000;
//double step;
//#define NUM_THREADS 512
//
//void main()
//{
//	int i;
//	clock_t start, stop;
//	start = clock();
//	//串行计算
//	double x, pi, sum[NUM_THREADS];
//	step = 1.0 / (double)num_steps;
//	omp_set_num_threads(NUM_THREADS);//******
//	printf("Procs: %d, Thread: %d \n", omp_get_num_procs(), omp_get_max_threads());
//#pragma omp parallel //******
//	{
//		double x;
//		int id;
//		id = omp_get_thread_num();
//		sum[id] = 0; //**
//#pragma omp for//******
//		for (i = 0; i < num_steps; i++) {
//			x = (i + 0.5) * step;
//			sum[id] += 4.0 / (1.0 + x * x);
//		}
//	}
//	for (i = 0, pi = 0.0; i < NUM_THREADS; i++)pi += sum[i] * step;
//	stop = clock();
//	printf("PI: %f\n", pi);
//		double parallel = ((double)stop - start) / CLOCKS_PER_SEC * 1000.0;
//	printf("CPU Parallel time: %3f ms\n", parallel);//并行时间
//
//
//	start = clock();
//	double  sum2 = 0.0;
//	step = 1.0 / (double)num_steps;
//	for (i = 0; i < num_steps; i++) {
//		x = (i + 0.5) * step;
//		sum2 = sum2 + (double)4.0 / (1.0 + x * x);
//	}
//	pi = step * sum2;
//
//	stop = clock();
//	printf("PI: %f\n", pi);
//	double serial = ((double)stop - start) / CLOCKS_PER_SEC * 1000.0;
//	printf("CPU Serial time: %3f ms\n", serial);//并行时间
//	printf("S0: %3f\n", serial / parallel);
//}
