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
//    auto t1 = Clock::now();//��ʱ��ʼ
//
////    //method1 ������
////    int sum = 0;
////#pragma omp parallel for reduction(+:sum)
////    for (int i = 0; i < 100; i++)
////        if (i < 50)
////            sum += 1;//smallwork()
////        else
////            //bigwork()
////            for (int j = 0; j < 1000000; j++)
////                sum += 1;
//
////    //method2 ����
//    int sum = 0;
//#pragma omp parallel for reduction(+:sum)
//    for (int i = 0; i < 100; i++)
//        if (i % 2)
//            sum += 1;//smallwork()
//        else
//            //bigwork()
//            for (int j = 0; j < 1000000; j++)
//                sum += 1;
//
//
//    printf("Final result= %d\n", sum);
//
//
//    auto t2 = Clock::now();//��ʱ����
//    std::cout << "Time(ns)= " << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() << '\n';
//
//
//}