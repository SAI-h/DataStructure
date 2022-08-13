/*生产者和消费者问题*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

const int N = 10;
int buffer[10];
int in, out;
sem_t empty, full, mutex;

void *producer(void *arg) {
    int tag = pthread_self() % 100;
    srand(time(NULL) + tag);
    int nextpro;
    while(1) {
        nextpro = rand() % 97;
        sem_wait(&empty);        
        sem_wait(&mutex);
        buffer[in] = nextpro;
        printf("The producer %d has put the product %d in the location %d.\n", tag, nextpro, in);
        in = (in + 1) % N;
        sem_post(&mutex);
        sem_post(&full);
        usleep(1000 * 1000 / (rand() % 20 + 1));
    }
}

void *consumer(void *arg) {
    int tag = pthread_self() % 100;
    int item;
    while(1) {
        sem_wait(&full);
        sem_wait(&mutex);
        item = buffer[out];
        printf("The consumer %d has consumed the product %d which located in %d.\n", tag, item, out);
        out = (out + 1) % N;
        sem_post(&mutex);
        sem_post(&empty);
        usleep(1000 * 1000 / (rand() % 20 + 1));
    }
}

int main(void) {
    pthread_t tid[2];
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, N);
    pthread_create(&tid[0], NULL, producer, NULL);
    pthread_create(&tid[1], NULL, consumer, NULL);
    for(int i = 0; i < 2; i ++) pthread_join(tid[i], NULL);
    printf("Main over!\n");
    return 0;
}