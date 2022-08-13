/*
[2011统考真题].某银行提供1个服务窗口和10个供顾客等待的座位.顾客到达银行的时候若有空座位,
则到取号机上领取一个号,等待叫号.取号机每次允许一位顾客使用.当营业员空闲的时候,通过叫号选取一个顾客,并为其服务.
请实现其同步与互斥.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

int waitingQueue[10], front, rear; // 等候队列
sem_t seats; // 座位
sem_t mutex; // 互斥
sem_t cust; // 顾客数

void *customer(void *arg) {
    int id = *(int *)arg;
    sem_wait(&seats); // 查看是否有座位
    sem_wait(&mutex); // 取号加入等待队列
    waitingQueue[rear] = id;
    rear = (rear + 1) % 10;
    printf("customer_%d ask for the service!\n", id);
    sem_post(&mutex);
    sem_post(&cust);
    // p(service) // 请求服务
    usleep(1000 * 1000 / (rand() % 20 + 1));
}

void *clerk(void *arg) {
    while(1) {
        sem_wait(&cust); // 是否有顾客
        sem_wait(&mutex); // 叫号
        int id = waitingQueue[front];
        front = (front + 1) % 10;
        sem_post(&mutex);
        sem_post(&seats);
        // v(service) // 响应服务
        printf("Provide service for customer_%d!\n", id);
        usleep(1000 * 1000 / (rand() % 20 + 1));
    }
}

int main(void) {
    srand((size_t)time(NULL));
    sem_init(&seats, 0, 10);
    sem_init(&mutex, 0, 1);
    pthread_t _clerk;
    pthread_create(&_clerk, NULL, clerk, NULL);
    int id = 0;
    while(1) {
        pthread_t _customer;
        pthread_create(&_customer, NULL, customer, &id);
        id ++;
    }
    return 0;
}