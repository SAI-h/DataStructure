/*
多生产者多消费者的多缓冲区问题
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t empty, full, mutex;
int buffer[10];
int in, out;

void *producer(void *arg) {
    while(1) {
        int producerID = pthread_self() % 100;
        int item = rand() % 100;
        sem_wait(&empty);
        sem_wait(&mutex);
        buffer[in] = item;
        printf("The producer %d has put the product %d in the location %d.\n", producerID, item, in);
        in = (in + 1) % 10;
        sem_post(&mutex);
        sem_post(&full);
        usleep(1000 * 1000 / (rand() % 20 + 1));
    }
}

void *consumer(void  *arg) {
    while(1) {
        int consumerID = pthread_self() % 100;
        sem_wait(&full);
        sem_wait(&mutex);
        int item = buffer[out];
        printf("The consumer %d has consumed the product %d in the location %d.\n", consumerID, item, out);
        out = (out + 1) % 10;
        sem_post(&mutex);
        sem_post(&empty);
        usleep(1000 * 1000 / (rand() % 20 + 1));
    }
}

int main(void) {
    sem_init(&mutex, 0, 1);
    sem_init(&empty, 0, 10);
    sem_init(&full, 0, 0);
    srand((size_t)time(NULL));
    int numOfpro, numOfCons;
    printf("Please input the number of producers:");
    scanf("%d", &numOfpro);
    printf("Please input the number of consumers:");
    scanf("%d", &numOfCons);
    pthread_t tid[numOfpro + numOfCons];
    for(int i = 0; i < numOfpro; i ++) pthread_create(&tid[i], NULL, producer, NULL);
    for(int i = numOfpro; i < numOfpro + numOfCons; i ++) pthread_create(&tid[i], NULL, consumer, NULL);
    for(int i = 0; i < numOfpro + numOfCons; i ++) pthread_join(tid[i], NULL);
    return 0;
}

/*
Please input the number of producers:3
Please input the number of consumers:4
The producer 96 has put the product 30 in the location 0.
The producer 52 has put the product 4 in the location 1.
The producer 8 has put the product 8 in the location 2.
The consumer 64 has consumed the product 30 in the location 0.
The consumer 20 has consumed the product 4 in the location 1.
The consumer 76 has consumed the product 8 in the location 2.
The producer 52 has put the product 54 in the location 3.
The consumer 32 has consumed the product 54 in the location 3.
The producer 52 has put the product 3 in the location 4.
The consumer 20 has consumed the product 3 in the location 4.
The producer 96 has put the product 36 in the location 5.
The producer 8 has put the product 75 in the location 6.
The consumer 64 has consumed the product 36 in the location 5.
The consumer 76 has consumed the product 75 in the location 6.
The producer 52 has put the product 47 in the location 7.
The consumer 32 has consumed the product 47 in the location 7.
The producer 96 has put the product 33 in the location 8.
The consumer 76 has consumed the product 33 in the location 8.
The producer 96 has put the product 56 in the location 9.
The consumer 32 has consumed the product 56 in the location 9.
The producer 52 has put the product 44 in the location 0.
The consumer 20 has consumed the product 44 in the location 0.
The producer 52 has put the product 48 in the location 1.
The consumer 64 has consumed the product 48 in the location 1.
The producer 52 has put the product 85 in the location 2.
The consumer 76 has consumed the product 85 in the location 2.
The producer 52 has put the product 16 in the location 3.
The consumer 20 has consumed the product 16 in the location 3.
The producer 52 has put the product 57 in the location 4.
The consumer 32 has consumed the product 57 in the location 4.
The producer 96 has put the product 40 in the location 5.
The consumer 64 has consumed the product 40 in the location 5.
The producer 96 has put the product 75 in the location 6.
The consumer 76 has consumed the product 75 in the location 6.
The producer 52 has put the product 48 in the location 7.
The consumer 32 has consumed the product 48 in the location 7.
The producer 8 has put the product 59 in the location 8.
The consumer 64 has consumed the product 59 in the location 8.
The producer 96 has put the product 6 in the location 9.
The consumer 76 has consumed the product 6 in the location 9.
The producer 52 has put the product 21 in the location 0.
The consumer 64 has consumed the product 21 in the location 0.
The producer 52 has put the product 39 in the location 1.
The consumer 76 has consumed the product 39 in the location 1.
The producer 96 has put the product 14 in the location 2.
The producer 52 has put the product 61 in the location 3.
The consumer 64 has consumed the product 14 in the location 2.
The consumer 32 has consumed the product 61 in the location 3.
The producer 52 has put the product 92 in the location 4.
The consumer 20 has consumed the product 92 in the location 4.
The producer 52 has put the product 30 in the location 5.
The consumer 64 has consumed the product 30 in the location 5.
The producer 8 has put the product 95 in the location 6.
The consumer 32 has consumed the product 95 in the location 6.
The producer 52 has put the product 15 in the location 7.
The consumer 76 has consumed the product 15 in the location 7.
The producer 96 has put the product 99 in the location 8.
...
*/