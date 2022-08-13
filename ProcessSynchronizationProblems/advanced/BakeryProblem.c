/*
面包店有很多面包,由n名销售人员推销,每名顾客进店后取一个号,并且等待叫号,当一名销售人员空闲时,
就叫下一个号.试设计一个使推销人员和顾客同步的算法.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

int n; // n名推销人员
int buffer[100], front, rear; // 叫号队列
int number; // 号码

sem_t mutex; // 互斥
sem_t full, empty; // full:标记有多少顾客, empty:标记顾客可以取号的量

void *saleman(void *arg) {
    int id = *(int *)arg;
    while(1) {
        sem_wait(&full); // 有顾客吗?
        sem_wait(&mutex); // 叫号
        int num = buffer[front];
        printf("Waiter %d calls customer numbered %d.\n", id, num);
        front = (front + 1) % 100;
        sem_post(&mutex);
        sem_post(&empty);
        // 服务
    }
}

void *customer(void *arg) {
    sem_wait(&empty);
    sem_wait(&mutex); // 取号
    buffer[rear] = number;
    printf("Customer %ld's number %d.\n", pthread_self() % 100, number);
    number ++;
    rear = (rear + 1) % 100;
    sem_post(&mutex);
    sem_post(&full); // 请求服务
}

int main(void) {
    srand((size_t)time(NULL));
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 100);
    sem_init(&full, 0, 0);
    n = rand() % 100 + 1;
    pthread_t tid[n];
    for(int i = 0; i < n; i ++) pthread_create(tid + i, NULL, saleman, &i);
    while(1) {
        pthread_t _customer;
        pthread_create(&_customer, NULL, customer, NULL);
    }
    return 0;
}