/*哲学家进餐问题*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t mutex, chopsitick[5];

void *philosopher(void *arg) {
    int i = *(int *)arg;
    while(1) {
        sem_wait(&mutex);
        sem_wait(&chopsitick[i]);
        sem_wait(&chopsitick[(i + 1) % 5]);
        printf("The %dth philosopher picked up chopsiticks marked %d and %d.\n", i, i, (i + 1) % 5);
        sem_post(&mutex);
        printf("The %dth philosopher is eating now.\n", i);
        sem_post(&chopsitick[i]);
        sem_post(&chopsitick[(i + 1) % 5]);
        printf("The %dth philosopher picked down chopsiticks marked %d and %d.\n", i, i, (i + 1) % 5);
        printf("The %dth philosopher is thinking now.\n", i);
    }
}

int main(void) {
    sem_init(&mutex, 0, 1);
    int ID[5] = {0, 1, 2, 3, 4}; 
    for(int i = 0; i < 5; i ++) sem_init(&chopsitick[i], 0, 1);
    pthread_t tid[5];
    for(int i = 0; i < 5; i ++) pthread_create(&tid[i], NULL, philosopher, &ID[i]); // 传入参数,判定哲学家的序号(直接传参&i会错？？因为会传入的是i++以后的值)
    for(int i = 0; i < 5; i ++) pthread_join(tid[i], NULL);
    return 0;
}

/*
The 0th philosopher picked up chopsiticks marked 0 and 1.
The 0th philosopher is eating now.
The 2th philosopher picked up chopsiticks marked 2 and 3.
The 2th philosopher is eating now.
The 2th philosopher picked down chopsiticks marked 2 and 3.
The 3th philosopher picked up chopsiticks marked 3 and 4.
The 3th philosopher is eating now.
The 3th philosopher picked down chopsiticks marked 3 and 4.
The 4th philosopher picked up chopsiticks marked 4 and 0.
The 4th philosopher is eating now.
The 1th philosopher picked up chopsiticks marked 1 and 2.
The 3th philosopher is thinking now.
The 3th philosopher picked up chopsiticks marked 3 and 4.
The 0th philosopher picked down chopsiticks marked 0 and 1.
The 0th philosopher is thinking now.
The 1th philosopher is eating now.
The 1th philosopher picked down chopsiticks marked 1 and 2.
The 0th philosopher picked up chopsiticks marked 0 and 1.
The 0th philosopher is eating now.
...
*/