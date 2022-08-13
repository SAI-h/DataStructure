/*
某工厂有两个生产车间和一个装配车间,两个生产车间分别生产A,B两种零件,装配车间的任务是把
A、B两种零件组装成产品.两个生产车间每生产一个零件后,都要分别把它们送到装配车间的货架F1、F2上.
F1存放零件A,F2存放零件B,F1和F2的容量均为10.装配工人每次从货架上取一个零件A和一个零件B之后组装成产品,
请用P,V操作进行正确管理.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t full_F1, full_F2; // 表示F1、F2货架上占用的位置数目的信号量
sem_t empty_F1, empty_F2; // 表示F1、F2货架上未被占用的位置数目的信号量
sem_t mutex1, mutex2; // 互斥地访问两个货架

void *AtoF1(void *arg) {
    while(1) {
        // produce A
        sem_wait(&empty_F1);
        sem_wait(&mutex1);
        printf("There's an A part on the F1 shelf!\n");
        sem_post(&mutex1);
        sem_post(&full_F1);
        // usleep(1000 * 1000 / 20);
    }
}

void *BtoF2(void *arg) {
    while(1) {
        // produce B
        sem_wait(&empty_F2);
        sem_wait(&mutex2);
        printf("There's a B part on the F2 shelf!\n");
        sem_post(&mutex2);
        sem_post(&full_F2);
        // usleep(1000 * 1000 / 20);
    }
}

void *fitParts(void *arg) {
    while(1) {
        sem_wait(&full_F1);
        sem_wait(&mutex1);
        printf("An A part removed from shelf F1!\n");
        sem_post(&mutex1);
        sem_post(&empty_F1);

        sem_wait(&full_F2);
        sem_wait(&mutex2);
        printf("A B part removed from shelf F2!\n");
        sem_post(&mutex2);
        sem_post(&empty_F2);
        printf("A and B are assembled!\n");
        // usleep(1000 * 1000 / 20);
    }
}

int main(void) {
    sem_init(&empty_F1, 0, 10);
    sem_init(&empty_F2, 0, 10);
    sem_init(&full_F1, 0, 0);
    sem_init(&full_F2, 0, 0);
    sem_init(&mutex1, 0, 1);
    sem_init(&mutex2, 0, 1);

    pthread_t tid[3]; // 真实的生产环境会有多个AtoF1、BtoF2以及fitParts进程(线程),因为工人可能不止一个
    pthread_create(&tid[0], NULL, AtoF1, NULL);
    pthread_create(&tid[1], NULL, BtoF2, NULL);
    pthread_create(&tid[2], NULL, fitParts, NULL);

    for(int i = 0; i < 3; i ++) pthread_join(tid[i], NULL);

    return 0;
}