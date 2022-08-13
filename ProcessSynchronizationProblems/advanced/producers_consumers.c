/*
[2014统考真题].系统中有多个生产者进程和多个消费者进程,共享一个能存放1000件产品的环形缓冲区(初始为空).
缓冲区未满时,生产者进程可以进入其生产的一件产品,否则等待;缓冲区未空时,消费者进程可以从缓冲区取走一件产品,否则等待.
要求一个消费者进程从缓冲区取出10件产品后,其他消费者进程才可以取产品.请实现其同步和互斥.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t empty, full;
sem_t mutex; // 缓冲区互斥
sem_t mutex_2; // 消费者之间的互斥

int buffer[1000], front, rear;

void *producer(void *arg) {
    while(1) {
        // 生产产品
        int item = rand() % 1000;
        sem_wait(&empty);
        sem_wait(&mutex);
        // 将产品放入缓冲区
        buffer[rear] = item;
        printf("producer%ld: %d --> buffer[%d]!\n", pthread_self() % 100, item, rear);
        rear = (rear + 1) % 1000;
        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg) {
    while(1) {
        sem_wait(&mutex_2);
        // 一次性取十个产品
        for(int i = 0; i < 10; i ++) {
            sem_wait(&full);
            sem_wait(&mutex);
            int item = buffer[front];
            printf("consumer%ld: buffer[%d] --> %d(%d)!\n", pthread_self() % 100, front, item, i);
            front = (front + 1) % 1000;
            sem_post(&mutex);
            sem_post(&empty);
        }
        sem_post(&mutex_2);
        // 消费产品
        usleep(1000 * 1000 / (rand() % 20 + 1));
    }
}

void *create_producer(void *arg) {
    while(1) {
        pthread_t _producer;
        pthread_create(&_producer, NULL, producer, NULL);
    }
}

void *create_consumer(void *arg) {
    while(1) {
        pthread_t _consumer;
        pthread_create(&_consumer, NULL, consumer, NULL);
    }
}

int main(void) {
    srand((size_t)time(NULL));
    sem_init(&empty, 0, 1000);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    sem_init(&mutex_2, 0, 1);
    pthread_t root[2];
    pthread_create(root, NULL, create_producer, NULL);
    pthread_create(root + 1, NULL, create_consumer, NULL);
    for(int i = 0; i < 2; i ++) pthread_join(root[i], NULL); // 不会执行到
    return 0;
}

/*
...
consumer40: buffer[350] --> 771(0)!
producer76: 158 --> buffer[350]!
consumer40: buffer[351] --> 779(1)!
consumer40: buffer[352] --> 905(2)!
producer24: 293 --> buffer[351]!
producer24: 611 --> buffer[352]!
consumer40: buffer[353] --> 484(3)!
consumer40: buffer[354] --> 791(4)!
producer72: 485 --> buffer[353]!
consumer40: buffer[355] --> 997(5)!
producer36: 292 --> buffer[354]!
producer36: 44 --> buffer[355]!
consumer40: buffer[356] --> 675(6)!
consumer40: buffer[357] --> 481(7)!
consumer40: buffer[358] --> 856(8)!
producer4: 982 --> buffer[356]!
producer4: 437 --> buffer[357]!
producer4: 921 --> buffer[358]!
consumer40: buffer[359] --> 374(9)!
producer36: 628 --> buffer[359]!
consumer52: buffer[360] --> 400(0)!
producer4: 561 --> buffer[360]!
consumer52: buffer[361] --> 704(1)!
consumer52: buffer[362] --> 169(2)!
producer4: 729 --> buffer[361]!
producer4: 899 --> buffer[362]!
consumer52: buffer[363] --> 826(3)!
consumer52: buffer[364] --> 151(4)!
producer48: 997 --> buffer[363]!
producer48: 17 --> buffer[364]!
consumer52: buffer[365] --> 271(5)!
producer48: 379 --> buffer[365]!
consumer52: buffer[366] --> 429(6)!
consumer52: buffer[367] --> 628(7)!
producer32: 692 --> buffer[366]!
producer32: 785 --> buffer[367]!
consumer52: buffer[368] --> 867(8)!
consumer52: buffer[369] --> 580(9)!
producer44: 809 --> buffer[368]!
producer44: 792 --> buffer[369]!
consumer64: buffer[370] --> 632(0)!
consumer64: buffer[371] --> 325(1)!
producer44: 158 --> buffer[370]!
producer44: 801 --> buffer[371]!
consumer64: buffer[372] --> 305(2)!
producer68: 121 --> buffer[372]!
consumer64: buffer[373] --> 68(3)!
consumer64: buffer[374] --> 903(4)!
producer24: 201 --> buffer[373]!
producer24: 870 --> buffer[374]!
consumer64: buffer[375] --> 569(5)!
producer68: 41 --> buffer[375]!
consumer64: buffer[376] --> 932(6)!
producer72: 786 --> buffer[376]!
consumer64: buffer[377] --> 567(7)!
producer64: 227 --> buffer[377]!
consumer64: buffer[378] --> 481(8)!
consumer64: buffer[379] --> 538(9)!
producer72: 356 --> buffer[378]!
producer72: 386 --> buffer[379]!
consumer76: buffer[380] --> 334(0)!
consumer76: buffer[381] --> 238(1)!
producer80: 524 --> buffer[380]!
producer80: 674 --> buffer[381]!
consumer76: buffer[382] --> 609(2)!
consumer76: buffer[383] --> 708(3)!
producer84: 784 --> buffer[382]!
producer84: 384 --> buffer[383]!
consumer76: buffer[384] --> 915(4)!
consumer76: buffer[385] --> 101(5)!
producer12: 255 --> buffer[384]!
producer12: 344 --> buffer[385]!
consumer76: buffer[386] --> 203(6)!
producer48: 884 --> buffer[386]!
consumer76: buffer[387] --> 307(7)!
consumer76: buffer[388] --> 172(8)!
producer96: 196 --> buffer[387]!
producer96: 762 --> buffer[388]!
consumer76: buffer[389] --> 326(9)!
producer76: 321 --> buffer[389]!
consumer88: buffer[390] --> 699(0)!
producer60: 460 --> buffer[390]!
consumer88: buffer[391] --> 872(1)!
producer68: 628 --> buffer[391]!
consumer88: buffer[392] --> 401(2)!
producer48: 848 --> buffer[392]!
consumer88: buffer[393] --> 322(3)!
producer84: 273 --> buffer[393]!
consumer88: buffer[394] --> 322(4)!
producer96: 377 --> buffer[394]!
consumer88: buffer[395] --> 995(5)!
producer8: 242 --> buffer[395]!
consumer88: buffer[396] --> 189(6)!
producer32: 679 --> buffer[396]!
consumer88: buffer[397] --> 265(7)!
producer72: 377 --> buffer[397]!
consumer88: buffer[398] --> 821(8)!
consumer88: buffer[399] --> 615(9)!
producer40: 345 --> buffer[398]!
...
*/