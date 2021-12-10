#include<iostream>
#include<stdio.h>
#include<malloc.h>
using namespace std;
enum process_status{READY , RUN , FINISH}; //进程的三种状态
//定义进程数据结构
struct PCB
{
    int process_tag ; //存储进程标识符
    struct pcb *next ; //连接下一个进程的指针
    int priority ; //优先调度算法中为优先级 ， 轮转调度算法中为轮转时间片
    int cputime ; //占用CPU时间片数
    int alltime ; //进程所需时间片数
    process_status status ; //进程当前的状态
};
//定义进程控制块的链结构
struct PCBC
{
    PCB *run ; //当前运行的进程指针
    PCB *ready ; //当前准备队列的头指针
    PCB *tail ; //准备队列的队尾指针
    PCB *finish ; //完成队列的指针
} PCBC ;
void init_pcbc(PCBC *p)
{
    p->run = NULL ;
    p->ready = NULL ;
    p->tail = NULL ;
    p->finish = NULL ;
}
//输入进程，并加入就绪队列
void input_process(PCBC *pcbc,int num)
{
    PCB *pcb ;
    pcb = (PCB*)malloc(sizeof(PCB)) ;
    pcb->process_tag=rand()%1000+1000;
    pcb->priority=rand()%83+1;
    pcb->cputime=0;
    pcb->alltime=rand()%8+1;
    pcb->status = READY ; //初始化就绪状态
    //当就绪队列为空时
    if(pcbc->ready == NULL && pcbc->tail == NULL)
    {
        pcbc->ready = pcbc->tail = pcb ;
        pcb->next = NULL ;
    }
    else
    {
        //将新进入的队列加入队尾
        pcb->next = pcbc->tail->next ;
        pcbc->tail->next = pcb ;
        pcbc->tail = pcb ;
    }
}
void swapx(PCB  * p1 , PCB *p2)
{
    int  i , priority , cputime , alltime ;
    int temp ;
    temp = p1->process_tag;
    p1->process_tag = p2->process_tag ;
    p2->process_tag= temp ;
    //优先值的交换
    priority = p1->priority ;
    p1->priority = p2->priority ;
    p2->priority = priority ;
    //占用CPU时间片的交换
    cputime = p1->cputime ;
    p1->cputime = p2->cputime ;
    p2->cputime = cputime ;
    //进程所需时间片数的交换
    alltime = p1->alltime ;
    p1->alltime = p2->alltime ;
    p2->alltime = alltime ;
}
//将就绪队列按优先级别大小进行排序,按冒泡排序算法
void sort_pcbc(PCBC *pcbc , int pcb_num)
{
    PCB *p  , *p1 ;
    p = pcbc->ready ;
   for(p = pcbc->ready ; p != NULL ; p = p->next)
   {
       for(p1 = p->next ; p1 != NULL ; p1 = p1->next)
       {
           if(p->priority < p1->priority)
           {
               swapx(p , p1) ; //只是进行指针内部数据的交换，不改变指针指向
           }
       }
   }
}

// 打印当前进程控制块中的情况
 void print_log(PCBC *pcbc)
 {
     PCB *ready , *finish ;
     ready = pcbc->ready ;
     finish = pcbc->finish ;
     printf("==========================\n") ;
     printf("RUNNING PROC: \n") ;
     if(pcbc->run != NULL)
     {
        printf("%4d  %4d  %4d  %4d \n" , pcbc->run->process_tag ,pcbc->run->priority , pcbc->run->cputime , pcbc->run->alltime) ;
     }
     else
     {
         printf("QUEUE is empty! \n") ;
     }
     printf("WAITING PROC\n") ;
     while(ready != NULL)
     {
         printf("%4d  %4d  %4d  %4d \n" , ready->process_tag ,ready->priority , ready->cputime , ready->alltime) ;
         ready = ready->next ;
     }
     printf("FINISH PROC\n") ;
     while(finish != NULL)
     {
         printf("%4d  %4d  %4d  %4d \n" , finish->process_tag ,finish->priority , finish->cputime , finish->alltime) ;
         finish = finish->next ;
     }
 }

// 运行进程控制块
void run_pcbc_priority(PCBC *xpcbc)
{
    PCBC *pcbc = xpcbc ;
    PCB *temp , *pre , *tail ;
    //进行那个CPU的循环调用
    while(pcbc->ready != NULL)
    {
        pcbc->run = pcbc->ready ; //将就绪队列队首加入运行队列
        pcbc->ready = pcbc->ready->next ; //改变队首元素
        print_log(pcbc) ;
        pcbc->run->priority -= 3 ;
        pcbc->run->alltime -= 1 ;
        if(pcbc->run->alltime == 0)
        {
        if(pcbc->finish == NULL)
        {
            pcbc->finish = pcbc->run ;
            pcbc->finish->next = NULL ;
            tail = pcbc->finish ;
        }
        else
        {
            tail->next = pcbc->run ;
            tail = tail->next ;
            tail->next = NULL ;
        }
        }
        else
        {
            if(pcbc->ready != NULL)
            {
                temp = pcbc->ready ;
                while(temp != NULL)
                {
                    if(pcbc->run->priority > temp->priority)
                    {
                        break ;
                    }
                    pre = temp ;
                    temp = temp->next ;
                }
                if(temp == pcbc->ready)
                {
                    pcbc->run->next = pcbc->ready ;
                    pcbc->ready = pcbc->run ;
                }
                else
                {
                pcbc->run->next = pre->next ;
                pre->next = pcbc->run ;
                }
            }
            else
            {
                pcbc->ready = pcbc->run ;
            }
        }
    }
    pcbc->run = NULL ;
    print_log(pcbc) ;
}

main()
{
    PCBC *pcbc ; //创建进程控制块链 ;
    int pcb_num=3 ; //记录处理进程数目
    pcbc = (PCBC*)malloc(sizeof(PCBC)) ;
    // printf("请输入要处理的进程数目： ") ;
    // scanf("%d" , &pcb_num) ;
    init_pcbc(pcbc) ; //初始化进程控制块链
    for(int i = 0 ; i < pcb_num ; i++)
    {
        input_process(pcbc,i) ; //输入所有进程，并进入就绪队列
    }
    //根据队列优先级进行排序
    sort_pcbc(pcbc , pcb_num) ;
    //通过优先调度算法运行
    printf("PRIORITY\n") ;
    run_pcbc_priority(pcbc) ;
}