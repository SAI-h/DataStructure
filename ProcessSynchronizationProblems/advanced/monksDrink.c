/*
寺庙中有若干小和尚和老和尚,有一个水缸,由小和尚提水入缸供老和尚饮用,
水缸可以容纳10桶水,水取自同一井中.水井径窄,每次只能容一个桶取水.水桶的总数为3个,
每次入缸取水仅为1桶水,且不可以同时进行.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t buckets; // 水桶
sem_t well_mutex, tank_mutex; // 井和水缸的互斥访问
sem_t full, empty; // 水缸的占用程度度量

// 老和尚
void *elder(void *arg) {
    while(1) {
        sem_wait(&full); // 如果水缸是空的,则不被允许取水, 如果sem_wait(&buckets)的语句在这之前,
                         // 要是有三个老和尚相继申请用水桶,那么水桶就没有可以使用的了(buckets=0),
                         // 那么当水缸中没有水的时候(full=0),就会产生死锁,因为没有水桶小和尚也没有办法打水,没有办法去增加full的值,
                         // 小和尚进程也是同理,要注意pv操作的次序
        sem_wait(&buckets); // 取水桶
        sem_wait(&tank_mutex);
        printf("Take out a bucket of water from the tank!\n");
        sem_post(&tank_mutex);
        sem_post(&empty);
        sem_post(&buckets);
        // usleep(1000 * 1000 / 20);
    }
}

// 小和尚
void *youth(void *arg) {
    while(1) {
        sem_wait(&empty); // 如果水缸是满的,则不被允许入水
        sem_wait(&buckets); // 取水桶
        sem_wait(&well_mutex); // 取水
        printf("Take a bucket of water from the well!\n");
        sem_post(&well_mutex);
        sem_wait(&tank_mutex); 
        printf("Put the water into the tank!\n");
        sem_post(&tank_mutex);
        sem_post(&full);
        sem_post(&buckets);
        // usleep(1000 * 1000 / 20);
    }
}

int main(void) {
    sem_init(&buckets, 0, 3);
    sem_init(&well_mutex, 0, 1);
    sem_init(&tank_mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, 10);
    int numOfYouth, numOfElder;
    printf("Please enter the number of young monks:");
    scanf("%d", &numOfYouth);
    printf("Please enter the number of old monks:");
    scanf("%d", &numOfElder);
    pthread_t tid[numOfYouth + numOfElder];
    for(int i = 0; i < numOfYouth; i ++) pthread_create(&tid[i], NULL, youth, NULL);
    for(int i = numOfYouth; i < numOfYouth + numOfElder; i ++) pthread_create(&tid[i], NULL, elder, NULL);
    for(int i = 0; i < numOfYouth + numOfElder; i ++) pthread_join(tid[i], NULL);
    return 0;
}