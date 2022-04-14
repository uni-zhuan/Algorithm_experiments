 //#include <omp.h>//eg4
 //#include<stdio.h>
 //#include<iostream>
 //#include<chrono>
 //using namespace std;
 //using namespace chrono;

 //int main()
 //{
 //    typedef std::chrono::high_resolution_clock Clock;
 //    auto t1 = Clock::now();//��ʱ��ʼ
 //    int sum = 0;
 ////    //method1 
 //    //for (int i = 0; i < 1000000; i++)
 //    //    sum += i;


 ////    //method2 
 ////#pragma omp parallel for
 ////    for (int i = 0; i < 1000000; i++)
 ////#pragma omp critical
 ////        sum += i;

 ////    //method3
 //#pragma omp parallel for reduction(+:sum)
 //    for (int i = 0; i < 1000000; i++)
 //        sum += i;



 //    printf("Final result= %d\n", sum);


 //    auto t2 = Clock::now();//��ʱ����
 //    std::cout << "Time(ns)= " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << '\n';

 //}