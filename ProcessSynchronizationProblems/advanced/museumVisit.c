/*
[2013统考真题].某博物馆最多可以容纳500人同时参观,有一个出入口,该出入口仅允许通过一个人,
参观者活动为:进门、参观、出门.请实现其同步和互斥
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t empty;
sem_t mutex;
int count;

void *visitor(void *arg) {
    sem_wait(&empty);
    sem_wait(&mutex);
    // 进门
    count ++;
    printf("A visitor enters the museum(count:%d)!\n", count);
    sem_post(&mutex);
    // 参观
    usleep(1000 * 1000 / (rand() % 20 + 1));
    sem_wait(&mutex);
    // 出门
    count --;
    printf("A visitor leaves the museum(count:%d)!\n", count);
    sem_post(&mutex);
    sem_post(&empty);
}

int main(void) {
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 500);
    while(1) {
        pthread_t _visitor;
        pthread_create(&_visitor, NULL, visitor, NULL);
    }
    return 0;
}