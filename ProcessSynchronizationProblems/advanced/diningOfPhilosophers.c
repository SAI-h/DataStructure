/*
有n(n≥3)名哲学家围坐在一张圆桌边,每名哲学家交替地就餐和思考.在圆桌中心有m(m≥1)个碗,每两名哲学家之间
有一根筷子.每名哲学家必须取到一个碗和两侧的筷子之后,才能就餐,就餐完毕,将碗和筷子放回原位,并继续思考.
为使得尽可能多的哲学家同时就餐,且防止出现死锁现象,请用信号量实现同步和互斥.

分析:
传统哲学家进餐问题中,限制最多允许n-1名哲学家同时抢筷子时,那么至少会有一名哲学家可以获得两根筷子顺利就餐,
这样就避免了死锁.本题可以用碗这个限制资源来避免死锁:当碗的数量小于哲学家的数量,本身就确保了不会是所有哲学家
同时争抢筷子的局面,也就不会发生死锁;当碗的数量大于等于哲学家的数量,为了让碗同样起到限制效果,可以让碗的资源量等于n-1,
这样就保证了最多有n-1名哲学家争抢进餐.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

int n, m; // n名哲学家(筷子数)、m只碗
sem_t *chopstick;
sem_t bowl;
// sem_t mutex; // 筷子必需一起分配

void *phil(void *arg) {
    int i = *(int *)arg;
    while(1) {
        sem_wait(&bowl); // 请求碗
        // sem_wait(&mutex);
        sem_wait(&chopstick[i]); // 申请筷子
        sem_wait(&chopstick[(i + 1) % n]);
        // sem_post(&mutex);
        printf("Philosopher%d is eating now!\n", i);
        sem_post(&bowl);
        sem_post(&chopstick[i]);
        sem_post(&chopstick[(i + 1) % n]);
        printf("Philosopher%d is thinking now!\n", i);
        usleep(1000 * 1000 / (rand() % 20 + 1));
    }
}

int main(void) {
    srand((size_t)time(NULL));
    n = rand() % 20 + 3, m = rand() % 20 + 1;
    chopstick = (sem_t *)malloc(sizeof(sem_t) * n);
    for(int i = 0; i < n; i ++) sem_init(chopstick + i, 0, 1);
    sem_init(&bowl, 0, m < n ? m : n - 1);
    // sem_init(&mutex, 0, 1);
    pthread_t ph[n];
    int i = 0, k = -1;
    while(i < n) {
        pthread_create(&ph[i], NULL, phil, &k);
        k ++;
        i ++;
    }
    for(int i = 0; i < n; i ++) pthread_join(ph[i], NULL);
    return 0;
}