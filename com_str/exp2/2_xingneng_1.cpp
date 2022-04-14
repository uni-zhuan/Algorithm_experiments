//#include <omp.h>//eg4
//#include<stdio.h>
//#include<iostream>
//#include<chrono>
//using namespace std;
//using namespace chrono;
//
//int main()
//{
//    typedef std::chrono::high_resolution_clock Clock;
//    auto t1 = Clock::now();//计时开始
//
//    int sum = 0;
//    //method 1
////#pragma omp parallel for reduction(+:sum)
////    for (int i = 0; i < 10000; i++)
////        sum += i;
//    //method2
//    for (int i = 0; i < 10000; i++)
//        sum += i;
//
//    printf("Final result= %d\n", sum);
//
//
//    auto t2 = Clock::now();//计时结束
//    std::cout <<"Time(ns)= "<< std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << '\n';
//
//
//}