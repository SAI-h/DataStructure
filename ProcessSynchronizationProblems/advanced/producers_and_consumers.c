/*
设P、Q、R共享一个缓冲区,P、Q构成一对生产者-消费者,R即位生产者又为消费者.
使用PV操作实现同步.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t full, empty;
int buffer;
int value; // full的值

void *P(void *arg) {
    while(1) {
        // produce
        int product = rand() % 100;
        sem_wait(&empty);
        // save
        buffer = product;
        printf("P1: Item %d has been stored in buffer!\n", buffer);
        sem_post(&full);
        usleep(1000 * 1000 / 20);
    }
}

void *Q(void *arg) {
    while(1) {
        sem_wait(&full);
        // consume
        printf("P2: Item %d has been taken out of the buffer!\n", buffer);
        sem_post(&empty);
        usleep(1000 * 1000 / 20);
    }
}

void *R(void *arg) {
    while(1) {
        sem_getvalue(&full, &value);
        if(value == 1) { // 缓冲区满
            sem_wait(&full);
            // consume
            printf("P3: Item %d has been taken out of the buffer!\n", buffer);
            sem_post(&empty);
        }else {
            // produce
            int product = rand() % 100;
            sem_wait(&empty);
            // save
            buffer = product;
            printf("P3: Item %d has been stored in buffer!\n", buffer);
            sem_post(&full);
        }
        usleep(1000 * 1000 / 20);
    }
}

int main(void) {
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 1);
    srand((size_t)time(NULL));
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, P, NULL);
    pthread_create(&tid[1], NULL, Q, NULL);
    pthread_create(&tid[2], NULL, R, NULL);
    for(int i = 0; i < 3; i ++) pthread_join(tid[i], NULL);
    return 0;
}