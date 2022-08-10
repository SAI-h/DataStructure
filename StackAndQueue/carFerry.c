/*
11.某汽车轮渡口,过江渡船每次能载10辆车过江.过江车辆分为客车类和货车类,上渡船有如下规定:
同类车先到先上船;客车先于火车上船,且每上4辆客车,才允许放上1辆货车;若等待客车不足4辆,则以货车代替;
若无货车等待,允许客车都上船.设计一个算法模拟渡口管理.

分析:
开辟三个队列:客车队列、货车队列、轮渡队列;
当客车进入时将其放入客车队列;当货车进入时将其放入货车队列;将每次调度的车辆放到轮渡队列.按照规则模拟即可.
*/

#include "relatedFun.c"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

queue pssqueue, vanqueue, ferryqueue; // 客车队列、货车队列和轮渡队列
sem_t pssempty; // 关于客车队列空缺的数量的信号量
sem_t vanempty; // 关于货车队列空缺的数量的信号量
sem_t mutex1, mutex2, mutex3; // 实现互斥操作
int total = 0, countPss = 0; // 轮渡队列中车的数量和被选中的客车数量

// 向客车队列中添加客车
void *passengerCar(void *arg) {
    int k = 1;
    while(1) {
        sem_wait(&pssempty); // 实际上等价于if(pssqueue不空) {...}; 用信号量控制也是类似的
        sem_wait(&mutex3);
        sem_wait(&mutex1);
        queuePush(pssqueue, k);
        printf("Psscar No.%d --> pssqueue\n", k ++);
        sem_post(&mutex1);
        sem_post(&mutex3);
        usleep(1000 * 1000 / (rand() % 1000 + 1));
    }
}

// 向货车队列中添加货车
void *van(void *arg) {
    int k = -1;
    while(1) {
        sem_wait(&vanempty);
        sem_wait(&mutex3);
        sem_wait(&mutex2);
        queuePush(vanqueue, k);
        printf("Van No.%d --> vanqueue\n", -(k --));
        sem_post(&mutex2);
        sem_post(&mutex3);
        usleep(1000 * 1000 / (rand() % 1000 + 1));
    }
}

// 完成调度
void *ferry(void *arg) {
    int k = 1;
    while(1) {
        while(total < 10) { // 选取(至多)十辆车上船
            if(countPss < 4) {
                // 因为队列判空的函数是实现了的,因此可以不用设置关于记录队列中占用的个数的信号量(如:pssfull、vanfull)
                if(!queueEmpty(pssqueue)) { // 客车队列不空,则每次从客车队列中选出一辆放入,每4个之后才允许放入一辆货车
                    sem_wait(&mutex1);
                    int topID = queueTop(pssqueue);
                    queuePush(ferryqueue, topID);
                    queuePop(pssqueue);
                    countPss ++;
                    total ++;
                    printf("Psscar NO.%d --> ferryqueue\n", topID);
                    sem_post(&pssempty);
                    sem_post(&mutex1);
                }else if(!queueEmpty(vanqueue)) { // 此时客车队列已经空了,用货车代替客车,满足4个车辆的要求,因为线程是并发运行的,因此下一个时刻客车队列中可能会有新的车辆进入
                    sem_wait(&mutex2);
                    int topID = queueTop(vanqueue);
                    queuePush(ferryqueue, topID);
                    queuePop(vanqueue);
                    countPss ++;
                    total ++;
                    printf("Van NO.%d --> ferryqueue\n", -topID);
                    sem_post(&vanempty);
                    sem_post(&mutex2);
                }
                // 可能会出现两个队列都是空的情况,但是当前面对的是多线程并发运行的情况,当切换到其他线程时会向队列中补充车辆
            }else {
                if(!queueEmpty(vanqueue)) { // 4+1模式中的1
                    sem_wait(&mutex2);
                    int topID = queueTop(vanqueue);
                    queuePush(ferryqueue, topID);
                    queuePop(vanqueue);
                    total ++;
                    countPss = 0;
                    printf("Van NO.%d --> ferryqueue\n", -topID);
                    sem_post(&vanempty);
                    sem_post(&mutex2);
                }else { // 没有货车了,将客车全部加入即可
                    sem_wait(&mutex1);
                    while(total < 10 && !queueEmpty(pssqueue)) {
                        int topID = queueTop(pssqueue);
                        queuePush(ferryqueue, topID);
                        queuePop(pssqueue);
                        total ++;
                        printf("Psscar NO.%d --> ferryqueue\n", topID);
                        sem_post(&pssempty);
                    }
                    if(total < 10) total = 10; // 若没有装满10辆车,这里选择了不再等待后续车辆的方式,直接将现在拥有的车辆全部送出
                    sem_post(&mutex1);
                }
            }
        }
        sem_wait(&mutex3);
        printf("There is the list of the %dth ferry:\n", k ++);
        while(!queueEmpty(ferryqueue)) {
            int topID = queueTop(ferryqueue);
            if(topID > 0) printf("psscar%d ", topID);
            else printf("van%d ", -topID);
            queuePop(ferryqueue);
        }
        printf("\n");
        total = countPss = 0;
        sem_post(&mutex3);
    }
}

int main(void) {
    initQueue(&pssqueue);
    initQueue(&vanqueue);
    initQueue(&ferryqueue);
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);
    sem_init(&mutex3, 0, 1);
    sem_init(&pssempty, 0, pssqueue -> capacity - 1);
    sem_init(&vanempty, 0, vanqueue -> capacity - 1);
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, passengerCar, NULL);
    pthread_create(&tid[1], NULL, van, NULL);
    pthread_create(&tid[2], NULL, ferry, NULL);
    for(int i = 0; i < 3; i ++) pthread_join(tid[i], NULL);
    return 0;
}

/*
可以验证有序性和调度的正确性
高速运行:
...
Psscar NO.36475 --> ferryqueue
Psscar NO.36476 --> ferryqueue
Psscar NO.36477 --> ferryqueue
Psscar No.36572 --> pssqueue
Psscar No.36573 --> pssqueue
Psscar No.36574 --> pssqueue
Psscar No.36575 --> pssqueue
Psscar No.36576 --> pssqueue
Psscar NO.36478 --> ferryqueue
Van No.9225 --> vanqueue
Van NO.9127 --> ferryqueue
Psscar No.36577 --> pssqueue
Psscar NO.36479 --> ferryqueue
Psscar NO.36480 --> ferryqueue
Psscar NO.36481 --> ferryqueue
Psscar NO.36482 --> ferryqueue
Van No.9226 --> vanqueue
Van NO.9128 --> ferryqueue
Psscar No.36578 --> pssqueue
Psscar No.36579 --> pssqueue
There is the list of the 4561th ferry:
psscar36475 psscar36476 psscar36477 psscar36478 van9127 psscar36479 psscar36480 psscar36481 psscar36482 van9128 

低速运行:
...
Psscar No.146 --> pssqueue
Psscar NO.146 --> ferryqueue
Van No.171 --> vanqueue
Van NO.171 --> ferryqueue
Van No.172 --> vanqueue
Van NO.172 --> ferryqueue
Van No.173 --> vanqueue
Van NO.173 --> ferryqueue
There is the list of the 73th ferry:
psscar146 van171 van172 van173 
Psscar No.141 --> pssqueue
Psscar NO.141 --> ferryqueue
Psscar No.142 --> pssqueue
Psscar NO.142 --> ferryqueue
Van No.168 --> vanqueue
Van NO.168 --> ferryqueue
Psscar No.143 --> pssqueue
Psscar NO.143 --> ferryqueue
There is the list of the 71th ferry:
psscar141 psscar142 van168 psscar143 
Van No.169 --> vanqueue
Psscar No.144 --> pssqueue
Van NO.169 --> ferryqueue
Psscar NO.144 --> ferryqueue
Van No.170 --> vanqueue
Van NO.170 --> ferryqueue
Psscar No.145 --> pssqueue
Psscar NO.145 --> ferryqueue
There is the list of the 72th ferry:
van169 psscar144 van170 psscar145 
Psscar No.146 --> pssqueue
Psscar NO.146 --> ferryqueue
Van No.171 --> vanqueue
Van NO.171 --> ferryqueue
Van No.172 --> vanqueue
Van NO.172 --> ferryqueue
Van No.173 --> vanqueue
Van NO.173 --> ferryqueue
There is the list of the 73th ferry:
psscar146 van171 van172 van173 
*/