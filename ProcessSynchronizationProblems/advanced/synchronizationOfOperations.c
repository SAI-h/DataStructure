/*
[2020统考真题].现有5个操作A、B、C、D、E,操作C必须在A和B完成之后执行,
操作E必须在C和D完成之后执行,请用PV操作实现操作间的同步.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t AC, BC;
sem_t CE, DE;

void *A(void *arg) {
    printf("A: finish the work!\n");
    sem_post(&AC);
}

void *B(void *arg) {
    printf("B: finish the work!\n");
    sem_post(&BC);
}

void *C(void *arg) {
    sem_wait(&AC);
    sem_wait(&BC);
    printf("C: finish the work!\n");
    sem_post(&CE);
}

void *D(void *arg) {
    printf("D: finish the work!\n");
    sem_post(&DE);
}

void *E(void *arg) {
    sem_wait(&CE);
    sem_wait(&DE);
    printf("E: finish the work!\n");
}

int main(void) {
    sem_init(&AC, 0, 0);
    sem_init(&BC, 0, 0);
    sem_init(&CE, 0, 0);
    sem_init(&DE, 0, 0);
    pthread_t tid[5];
    pthread_create(&tid[0], NULL, &A, NULL);
    pthread_create(&tid[1], NULL, &B, NULL);
    pthread_create(&tid[2], NULL, &C, NULL);
    pthread_create(&tid[3], NULL, &D, NULL);
    pthread_create(&tid[4], NULL, &E, NULL);
    for(int i = 0; i < 5; i ++) pthread_join(tid[i], NULL);
    return 0;
}