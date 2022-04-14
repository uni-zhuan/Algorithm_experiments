//#include <omp.h>
//#include <stdio.h>
//int main()
//{
//	int val = 8;
//#pragma omp parallel for firstprivate(val) lastprivate(val)
//	for(int i = 0; i < 2; i++){
//		printf("i=%d val=%d\n",i,val);
//		if (i == 1)
//			val = 10000;
//		printf("i=%d val=%d\n",i,val);
//	}
//	printf("val=%d\n", val);
//
//}