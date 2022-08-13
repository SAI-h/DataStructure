/*读者写者问题*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t rw; // 实现读写互斥
int reader_count = 0;
sem_t mutex; // 互斥访问reader_count
sem_t w; // 实现"写优先/读写公平"

void *reader(void *arg) {
    while(1) {
        sem_wait(&w); // w保证在writer处于临界区时,只有一个reader被阻塞于rw上,其余的reader会被阻塞在w上,
                      // 这使得,当一个reader获得rw在它处于临界区时,若此时来了一个writer,这个时候writer只需要等待这一个reader结束就可以抢占
                      // 否则,该writer可能要与多个reader抢占访问权
        sem_wait(&mutex);
        if(reader_count == 0) sem_wait(&rw);
        reader_count ++;
        sem_post(&mutex);
        sem_post(&w);
        printf("The reader %ld is reading the file now![Reading at the same time:%d]\n", pthread_self() % 100, reader_count);
        sem_wait(&mutex);
        reader_count --;
        if(reader_count == 0) sem_post(&rw);
        sem_post(&mutex);
        usleep(1000 * 1000 / (rand() % 20 + 1));
    }
}

void *writer(void *arg) {
    while(1) {
        sem_wait(&w);
        sem_wait(&rw);
        printf("The writer %ld is writing the file now!\n", pthread_self() % 100);
        sem_post(&rw);
        sem_post(&w);
        usleep(1000 * 1000 / (rand() % 20 + 1));
    }
}

int main(void) {
    sem_init(&rw, 0, 1);
    sem_init(&mutex, 0, 1);
    sem_init(&w, 0, 1);
    srand((size_t)time(NULL));
    int numOfReader, numOfWriter;
    printf("Please input the number of readers:");
    scanf("%d", &numOfReader);
    printf("Please input the number of writers:");
    scanf("%d", &numOfWriter);
    pthread_t tid[numOfReader + numOfWriter];
    for(int i = 0; i < numOfReader; i ++) pthread_create(&tid[i], NULL, reader, NULL);
    for(int i = numOfReader; i < numOfReader + numOfWriter; i ++) pthread_create(&tid[i], NULL, writer, NULL);
    for(int i = 0; i < numOfReader + numOfWriter; i ++) pthread_join(tid[i], NULL);
    return 0;
}

/*
The writer 56 is writing the file now!
The reader 16 is reading the file now![Reading at the same time:1]
The reader 92 is reading the file now![Reading at the same time:2]
The reader 4 is reading the file now![Reading at the same time:3]
The writer 20 is writing the file now!
The writer 12 is writing the file now!
The writer 40 is writing the file now!
The reader 40 is reading the file now![Reading at the same time:1]
The writer 76 is writing the file now!
The reader 12 is reading the file now![Reading at the same time:1]
The writer 24 is writing the file now!
The writer 4 is writing the file now!
The writer 68 is writing the file now!
The writer 44 is writing the file now!
The writer 48 is writing the file now!
The reader 56 is reading the file now![Reading at the same time:1]
The reader 84 is reading the file now![Reading at the same time:2]
The writer 96 is writing the file now!
The writer 52 is writing the file now!
...
*/