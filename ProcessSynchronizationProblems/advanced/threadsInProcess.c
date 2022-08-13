/*
[2017统考真题].某进程中有3个并发执行的线程thread1,thread2和thread3.请添加必要的信号量和PV操作,
要求确保线程互斥访问临界资源,并且最大限度地并发执行.

分析:
本题的关键点是题眼中的最大限度实现并发执行,三个全局变量中x只会被thread1单独调用因此无需设置信号量进行互斥,
y和z都存在多个线程访问因此需要实现互斥.但是如果对y和z的操作时涉及读和写的,读者和写者中读可以同时读,但是读和写、写和写的操作不能同时发生.
对每个变量都用单独的各自的信号量来实现互斥固然正确,但不能体现最大限度实现并发.如两个线程都要实现对某个变量的读操作,
理论上这个操作是可以同时进行的,但是因为仅设置一个互斥的信号量使得,一个线程在读的时候另一个线程只能等待.
thread1需要对y进行读操作,thread2需要对y、z进行读操作,thread3需要对z、y进行写操作.
对读操作而言可以采用计数,但因为读者数量较少,因此可以为读者进程单独分配不同的信号量,当需要对相应的变量进行写操作时需要同时请求这些信号量.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t mutex_y, mutex_z; // 全局变量的互斥访问

// 复数的结构类型定义
typedef struct {
    float a;
    float b;
} cnum;
cnum x, y, z; // 全局变量(临界资源)

sem_t mutex_y1; // 实现thread1和thread3对y的读写互斥
sem_t mutex_y2; // 实现thread2和thread3对y的读写互斥
sem_t mutex_z; // 实现对z的读写互斥

// 计算两个复数之和
cnum add(cnum p, cnum q) {
    cnum s;
    s.a = p.a + q.a;
    s.b = p.b + q.b;
    return s;
}

void *thread1(void *arg) {
    cnum w;
    sem_wait(&mutex_y1);
    w = add(x, y);
    sem_post(&mutex_y1);
    // ...
}

void *thread2(void *arg) {
    cnum w;
    sem_wait(&mutex_y2);
    sem_wait(&mutex_z);
    w = add(y, z);
    sem_post(&mutex_y2);
    sem_post(&mutex_z);
    // ...
}

void *thread3(void *arg) {
    cnum w;
    w.a = 1;
    w.b = 1;
    sem_wait(&mutex_z);
    z = add(z, w);
    sem_post(&mutex_z);
    sem_wait(&mutex_y1);
    sem_wait(&mutex_y2);
    y = add(y, w);
    sem_post(&mutex_y1);
    sem_post(&mutex_y2);
    // ...
}

int main(void) {
    sem_init(&mutex_y1, 0, 1);
    sem_init(&mutex_y2, 0, 1);
    sem_init(&mutex_z, 0, 1);
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, thread1, NULL);
    pthread_create(&tid[1], NULL, thread2, NULL);
    pthread_create(&tid[2], NULL, thread3, NULL);
    for(int i = 0; i < 3; i ++) pthread_join(tid[i], NULL);
    printf("Successfully!\n");
    return 0;
}