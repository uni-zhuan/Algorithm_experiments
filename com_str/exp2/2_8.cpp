//#include <omp.h>
//#include <stdio.h>
////threadprivate语句使一个全局文件作用域的变量在并行域内变成每个线程私有
//int alpha[10], beta[10], i;//eg3
//#pragma omp threadprivate(alpha) 
//int main()
//{
//	/* First parallel region */
//#pragma omp parallel private(i,beta)   
//	for (i = 0; i < 10; i++)
//		alpha[i] = beta[i] = i;
//	/* Second parallel region */
//#pragma omp parallel   
//	printf("alpha[3]= %d and beta[3]=%d\n", alpha[3], beta[3]);
//}
