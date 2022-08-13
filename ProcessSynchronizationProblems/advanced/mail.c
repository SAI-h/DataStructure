/*
[2015统考真题].有A、B两个人通过信箱进行辩论,每个人都从自己的信箱中取得对方的问题.将答案和向对方提出的新问题
组成一个邮件放入对方的邮箱中.假设A的信箱最多放M个邮件,B的信箱最多放N个邮件.初始时A的信箱中有x个邮件(0<x<M),
B的信箱中有y个邮件(0<y<N).辩论者每取出一个邮件,邮件数减1.A和B两个人的操作过程描述为:从自己的信箱中取出一个邮件、
回答问题并提出一个问题;将新邮件放入对方的信箱.
当信箱不空时,辩论者才能从信箱中取邮件,否则等待.当信箱不满时,辩论者才能将新邮件放入信箱,否则等待.
请实现其同步与互斥.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

int m, n; // A、B信箱中的邮件最大数量
int x, y; // A、B信箱中初始的邮件数量

sem_t emptyA, fullA;
sem_t emptyB, fullB;
sem_t mutexA, mutexB; // 虽然信箱是一人一个也要互斥,因为是一个信箱会被两个人操作,一个读一个写

void *A(void *arg) {
    while(1) {
        sem_wait(&fullA); // 从A的信箱中取出一个邮件
        sem_wait(&mutexA);
        printf("A: Put out a message!\n");
        sem_post(&mutexA);
        sem_post(&emptyA);
        // 回答问题 提出问题
        printf("A: Answer the question and ask a new question!\n"); 
        sem_wait(&emptyB); // 将新邮件放入B的邮箱
        sem_wait(&mutexB);
        printf("A: Put in a message!\n");
        sem_post(&mutexB);
        sem_post(&fullB); 
    }
}

void *B(void *arg) {
    while(1) {
        sem_wait(&fullB); // 从B的信箱中取出一个邮件
        sem_wait(&mutexB);
        printf("B: Put out a message!\n");
        sem_post(&mutexB);
        sem_post(&emptyB);
        // 回答问题 提出问题
        printf("B: Answer the question and ask a new question!\n"); 
        sem_wait(&emptyA); // 将新邮件放入A的邮箱
        sem_wait(&mutexA);
        printf("B: Put in a message!\n");
        sem_post(&mutexA);
        sem_post(&fullA); 
    }
}

int main(void) {
    srand((size_t)time(NULL));
    m = rand() % 100 + 1;
    n = rand() % 100 + 1;
    x = rand() % (m - 1) + 1; // (0, m)
    y = rand() % (n - 1) + 1; // (0, n)
    sem_init(&emptyA, 0, m - x);
    sem_init(&fullA, 0, x);
    sem_init(&emptyB, 0, n - y);
    sem_init(&fullB, 0, y);
    sem_init(&mutexA, 0, 1);
    sem_init(&mutexB, 0, 1);
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, A, NULL);
    pthread_create(&tid[1], NULL, B, NULL);
    for(int i = 0; i < 2; i ++) pthread_join(tid[i], NULL);
    return 0;
}