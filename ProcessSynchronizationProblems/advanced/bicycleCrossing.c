/*
南开大学和天津大学之间有一条弯曲的路,每次只允许一辆自行车通过,但中间有笑的安全岛M(同时允许两辆车通过),
可供已进入两端的两辆小车错车,请实现其同步与互斥.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t NT, TN;
sem_t NK, LT; // 对两侧小路进行的控制

void *N2T(void *arg) {
    sem_wait(&NT); // 保证同方向只能通行一辆车
    sem_wait(&NK); // 在路口观测,保证没有异方向的自行车在当前道路通行,如果有则等待其通过路口 
    printf("Direction_A %ld: N to K!\n", pthread_self() % 100);
    sem_post(&NK); // 行驶到了安全岛,任意时刻进入安全岛的车辆不会超过两辆(两个方向最多有一辆车)
    printf("Direction_A %ld: K to M!\n", pthread_self() % 100);
    sem_wait(&LT); // 同理,观测有无异方向的自行车在当前车辆通行,有则等待
    printf("Direction_A %ld: M to T!\n", pthread_self() % 100);
    sem_post(&LT);
    sem_post(&NT);
}

void *T2N(void *arg) {
    sem_wait(&TN);
    sem_wait(&LT);
    printf("Direction_B %ld: T to L!\n", pthread_self() % 100);
    sem_post(&LT);
    printf("Direction_B %ld: L to M!\n", pthread_self() % 100);
    sem_wait(&NK);
    printf("Direction_B %ld: M to N!\n", pthread_self() % 100);
    sem_post(&NK);
    sem_post(&TN);
}

void *createN2T(void *arg) {
    while(1) {
        pthread_t _N2T;
        pthread_create(&_N2T, NULL, N2T, NULL);
    }
}

void *createT2N(void *arg) {
    while(1) {
        pthread_t _T2N;
        pthread_create(&_T2N, NULL, T2N, NULL);
    }
}

int main(void) {
    sem_init(&NT, 0, 1);
    sem_init(&TN, 0, 1);
    sem_init(&NK, 0, 1);
    sem_init(&LT, 0, 1);
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, createN2T, NULL);
    pthread_create(&tid[1], NULL, createT2N, NULL);
    for(int i = 0; i < 2; i ++) pthread_join(tid[i], NULL);
    return 0;
}