/*
在一个仓库中可以存放A和B两种产品,要求:
1.每次只能存入一种产品
2.A产品数量-B产品数量 < M
3.B产品数量-A产品数量 < N
其中M、N为正整数,试描述A、B入库过程

分析:
每次只能存放一种产品,因此需要设置一个互斥访问的信号量
对于2、3两个不等式,分别动态了表示了A、B数量的上限
对于不等式2而言,B的增长不会对其产生"影响",因为B增长使得差值更小,不会使得其增长后不满足不等式,因此该不等式实际上是限制了A的增长
同理,对于不等式3而言,是限制了B的增长
因此这两个不等式实则是给定两个产品能够入库的指标,
若A超过了不等式2给定的指标限制只能被迫阻塞(wait),等待B的入库将新的指标释放出来(signal);
若B超过了不等式3给定的指标限制也只能被迫阻塞(wait),等待A的入库将新的指标释放出来(signal).
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t A_B, B_A, mutex;

// A入库
void *productA(void *arg) {
    while(1) {
        sem_wait(&A_B);
        sem_wait(&mutex);
        printf("A in.\n");
        sem_post(&mutex);
        sem_post(&B_A);
        usleep(1000 * 1000 / 20);
    }
}

// B入库
void *productB(void *arg) {
    while(1) {
        sem_wait(&B_A);
        sem_wait(&mutex);
        printf("B in.\n");
        sem_post(&mutex);
        sem_post(&A_B);
        usleep(1000 * 1000 / 20);
    }
}

int main(void) {
    int m, n;
    printf("Enter the upper limit M of A-B:");
    scanf("%d", &m);
    printf("Enter the upper limit N of B-A:");
    scanf("%d", &n);
    sem_init(&A_B, 0, m);
    sem_init(&B_A, 0, n);
    sem_init(&mutex, 0, 1);
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, productA, NULL);
    pthread_create(&tid[1], NULL, productB, NULL);
    for(int i = 0; i < 2; i ++) pthread_join(tid[i], NULL);
    return 0;
}