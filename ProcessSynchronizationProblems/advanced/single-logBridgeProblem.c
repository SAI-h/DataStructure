/*
存在一座桥,桥上的车流方向由南到北或者由北到南
1) 假设桥上每次只允许一辆车行驶,试用信号灯的pv操作实现交通管理
2) 假设桥上不允许两车交会,但允许同方向多俩车一次通过,试用信号灯的pv操作实现交通管理
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t mutex; // 桥的互斥访问
int count1 = 0, count2 = 0;
sem_t op1, op2;

void *NtoS(void *arg) {
    // 1)
    // sem_wait(&mutex);
    // // 由北到南有一辆车行驶过去了
    // sem_post(&mutex);
    sem_wait(&op1);
    if(count1 == 0) 
        sem_wait(&mutex);
    count1 ++;
    sem_post(&op1);
    printf("North to South: %d\t South to North:%d\n", count1, count2);
    sem_wait(&op1);
    count1 --;
    if(count1 == 0)
        sem_post(&mutex);
    sem_post(&op1);
}

void *StoN(void *arg) {
    // 1)
    // sem_wait(&mutex);
    // // 由南到北有一辆车行驶过去了
    // sem_post(&mutex);
    sem_wait(&op2);
    if(count2 == 0)
        sem_wait(&mutex);
    count2 ++;
    sem_post(&op2);
    printf("North to South: %d\t South to North:%d\n", count1, count2);
    sem_wait(&op2);
    count2 --;
    if(count2 == 0)
        sem_post(&mutex);
    sem_post(&op2);
}

int main(void) {
    sem_init(&mutex, 0, 1);
    sem_init(&op1, 0, 1);
    sem_init(&op2, 0, 1);
    int n, m;
    printf("Please input the number of vehicles from north to south:");
    scanf("%d", &n);
    printf("Please input the number of vehicles from south to north:");
    scanf("%d", &m);
    pthread_t tid[n + m];
    for(int i = 0; i < n; i ++) pthread_create(&tid[i], NULL, NtoS, NULL);
    for(int i = n; i < n + m; i ++) pthread_create(&tid[i], NULL, StoN, NULL);
    for(int i = 0; i < n + m; i ++) pthread_join(tid[i], NULL);
    return 0;
}