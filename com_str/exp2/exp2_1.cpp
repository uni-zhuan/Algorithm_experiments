//#include <omp.h>
//#include <stdio.h>
//int main()
//{
//	int nthreads, tid;
//	omp_set_num_threads(8);
//	printf("Hello from serial.\n");
//	printf("Thread number = % d\n", omp_get_thread_num());
//	
//#pragma omp parallel private(nthreads,tid)
//	{
//		tid = omp_get_thread_num();
//		printf("Hello World from OMP thread %d\n", tid);
//		if (tid == 0)
//		{
//			nthreads = omp_get_num_threads();
//			printf("Number of threads is %d\n", nthreads);
//		}
//	}
//	printf("Hello from serial again.\n");
//}
