/*
[2009统考真题].三个进程P1、P2、P3互斥使用一个包含N个单元的缓冲区,每次用produce()生成一个
正整数并用put()送入缓冲区某一个空单元;P2每次用getodd()从缓冲区取出一个奇数并用countodd()统计奇数个数;
P3每次用geteven()从该缓冲区取出一个偶数并用counteven()统计偶数个数.请实现其同步与互斥
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

int buffer[100];
int idx;
int numodd, numeven;

sem_t mutex; // 缓冲区的互斥访问
sem_t even, odd; // 标识缓冲区内现存的偶数和奇数的个数
sem_t empty; // 标识缓冲区内空缺的位置数目

// 生成一个随机数
int produce(int range) {
    return rand() % range;
}

// 放入缓冲区的空单元
void put(int item) {
    buffer[idx ++] = item; // 信号量控制不会越界
}

// 从缓冲区中取出一个奇数
int getodd() {
    int i = 0;
    while(buffer[i] % 2 == 0) i ++; // 信号量控制不会越界
    int res = buffer[i];
    for(int j = i; j < idx - 1; j ++) buffer[j] = buffer[j + 1];
    idx --;
    return res;
}

// 统计奇数个数
void countodd() {
    numodd ++;
}

// 从缓冲区中取出一个偶数
int geteven() {
    int i = 0;
    while(buffer[i] % 2 == 1) i ++; // 信号量控制不会越界
    int res = buffer[i];
    for(int j = i; j < idx - 1; j ++) buffer[j] = buffer[j + 1];
    idx --;
    return res;
}

// 统计偶数个数
void counteven() {
    numeven ++;
}

void *P1(void *arg) {
    while(1) {
        sem_wait(&empty);
        int item = produce(100);
        sem_wait(&mutex);
        put(item);
        printf("P1: %d --> buffer[%d].\n", item, idx);
        sem_post(&mutex);   
        if(item % 2) sem_post(&odd);
        else sem_post(&even);
    }
}

void *P2(void *arg) {
    while(1) {
        sem_wait(&odd);
        sem_wait(&mutex);
        int item = getodd();
        printf("P2: get odd %d.\n", item);
        countodd();
        printf("numodd: %d\n", numodd);
        sem_post(&mutex);
        sem_post(&empty);
    }
}

void *P3(void *arg) {
    while(1) {
        sem_wait(&even);
        sem_wait(&mutex);
        int item = geteven();
        printf("P3: get even %d.\n", item);
        counteven();
        printf("numeven: %d\n", numeven);
        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main(void) {
    srand((size_t)time(NULL));
    sem_init(&mutex, 0, 1);
    sem_init(&even, 0, 0);
    sem_init(&odd, 0, 0);
    sem_init(&empty, 0, 100);
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, P1, NULL);
    pthread_create(&tid[1], NULL, P2, NULL);
    pthread_create(&tid[2], NULL, P3, NULL);
    for(int i = 0; i < 3; i ++) pthread_join(tid[i], NULL);
    return 0;
}