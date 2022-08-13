/*
假设一个录像厅有1、2、3三种不同的录像片可由观众选择放映,录像厅的放映规则如下:
1.任意时刻,最多只能放映一种录像片,正在放映的录像片是自动循环放映的,最后一名观众主动离开时结束当前录像片的放映
2.选择当前正在放映的录像片的观众可以立即进入,允许同时多位选择同一种录像片的观众同时观看,同时观看的观众数量不限
3.等待观看其他录像片的观众按照到达顺序排队,当一种新的录像片开始放映时,所有等待观看该录像片的观众可依次进入录像厅同时观看.
用一个进程(这里用线程)代表一个观众.
用pv操作来实现.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t f_1, f_2, f_3; // 同步信号量
int count1, count2, count3; // 不同类型影片的观众数(动态变化)
sem_t op1, op2, op3; // 对三个count量的互斥更改

void *film_1(void *arg) {
    int id = *(int *)arg;
    sem_wait(&op1);
    if(count1 == 0) sem_wait(&f_1);
    count1 ++;
    sem_post(&op1);
    printf("Audience number %d starts watching the film_1!(count: %d)\n", id, count1);
    sem_wait(&op1);
    count1 --;
    if(count1 == 0) sem_post(&f_2); // 该影次的最后一名观众立场,告知等待的观众可以观影2号影片,
                                    // 因为给定条件时循环播放的,因此这里认为播放是按次序重复进行的(1->2->3->1...)
    sem_post(&op1);
    usleep(1000 * 1000);
}

void *film_2(void *arg) {
    int id = *(int *)arg;
    sem_wait(&op2);
    if(count2 == 0) sem_wait(&f_2);
    count2 ++;
    sem_post(&op2);
    printf("Audience number %d starts watching the film_2!(count: %d)\n", id, count2);
    sem_wait(&op2);
    count2 --;
    if(count2 == 0) sem_post(&f_3);
    sem_post(&op2);
    usleep(1000 * 1000);
}

void *film_3(void *arg) {
    int id = *(int *)arg;
    sem_wait(&op3);
    if(count3 == 0) sem_wait(&f_3);
    count3 ++;
    sem_post(&op3);
    printf("Audience number %d starts watching the film_3!(count: %d)\n", id, count3);
    sem_wait(&op3);
    count3 --;
    if(count3 == 0) sem_post(&f_1);
    sem_post(&op3);
    usleep(1000 * 1000);
}

int main(void) {
    sem_init(&f_1, 0, 1);
    sem_init(&f_2, 0, 0);
    sem_init(&f_3, 0, 0);
    sem_init(&op1, 0, 1);
    sem_init(&op2, 0, 1);
    sem_init(&op3, 0, 1);
    srand((size_t)time(NULL));
    int id = 1;
    while(1) { // 源源不断创建观众进程(线程)
        pthread_t audience;
        int choice = rand() % 3;
        if(choice == 0) pthread_create(&audience, NULL, film_1, &id);
        else if(choice == 1) pthread_create(&audience, NULL, film_2, &id);
        else pthread_create(&audience, NULL, film_3, &id);
        id ++;
        // pthread_join(audience, NULL); // 不加,不然观测不到并发的效果,一个线程创建后必须等当前线程结束才能开启下一个线程
    }
    // 子线程(创建)是死循环,这时就可以不用pthread_join来等待子线程,以免整个程序都阻塞
    return 0;
}

/*
Audience number 4 starts watching the film_1!(count: 1)
Audience number 3 starts watching the film_2!(count: 1)
Audience number 5 starts watching the film_2!(count: 2)
Audience number 6 starts watching the film_2!(count: 3)
Audience number 2 starts watching the film_3!(count: 1)
Audience number 7 starts watching the film_1!(count: 1)
Audience number 8 starts watching the film_2!(count: 1)
Audience number 17 starts watching the film_3!(count: 1)
Audience number 10 starts watching the film_1!(count: 1)
Audience number 13 starts watching the film_1!(count: 1)
Audience number 14 starts watching the film_1!(count: 2)
Audience number 16 starts watching the film_1!(count: 3)
Audience number 9 starts watching the film_2!(count: 1)
Audience number 12 starts watching the film_2!(count: 2)
Audience number 11 starts watching the film_2!(count: 2)
Audience number 20 starts watching the film_2!(count: 3)
Audience number 15 starts watching the film_2!(count: 4)
Audience number 18 starts watching the film_2!(count: 3)
Audience number 19 starts watching the film_3!(count: 1)
Audience number 21 starts watching the film_3!(count: 2)
Audience number 22 starts watching the film_1!(count: 1)
Audience number 24 starts watching the film_2!(count: 1)
Audience number 26 starts watching the film_3!(count: 1)
Audience number 24 starts watching the film_1!(count: 1)
Audience number 25 starts watching the film_2!(count: 1)
Audience number 29 starts watching the film_3!(count: 1)
Audience number 27 starts watching the film_1!(count: 1)
Audience number 28 starts watching the film_2!(count: 1)
Audience number 37 starts watching the film_3!(count: 1)
Audience number 30 starts watching the film_1!(count: 1)
Audience number 31 starts watching the film_2!(count: 1)
Audience number 35 starts watching the film_2!(count: 4)
Audience number 34 starts watching the film_2!(count: 3)
Audience number 32 starts watching the film_2!(count: 2)
Audience number 36 starts watching the film_2!(count: 4)
Audience number 40 starts watching the film_2!(count: 2)
Audience number 38 starts watching the film_3!(count: 1)
Audience number 33 starts watching the film_1!(count: 1)
Audience number 41 starts watching the film_1!(count: 2)
Audience number 39 starts watching the film_1!(count: 2)
Audience number 44 starts watching the film_2!(count: 1)
Audience number 42 starts watching the film_3!(count: 1)
Audience number 45 starts watching the film_3!(count: 2)
Audience number 43 starts watching the film_3!(count: 3)
Audience number 46 starts watching the film_1!(count: 1)
Audience number 51 starts watching the film_2!(count: 1)
Audience number 47 starts watching the film_3!(count: 1)
Audience number 48 starts watching the film_3!(count: 1)
Audience number 50 starts watching the film_3!(count: 3)
Audience number 49 starts watching the film_3!(count: 3)
Audience number 52 starts watching the film_3!(count: 3)
Audience number 53 starts watching the film_1!(count: 1)
Audience number 56 starts watching the film_2!(count: 1)
Audience number 57 starts watching the film_3!(count: 1)
Audience number 54 starts watching the film_1!(count: 1)
Audience number 55 starts watching the film_1!(count: 2)
Audience number 63 starts watching the film_2!(count: 1)
Audience number 60 starts watching the film_3!(count: 1)
Audience number 62 starts watching the film_3!(count: 2)
Audience number 58 starts watching the film_1!(count: 1)
Audience number 61 starts watching the film_1!(count: 3)
Audience number 59 starts watching the film_1!(count: 2)
Audience number 64 starts watching the film_2!(count: 1)
Audience number 67 starts watching the film_3!(count: 1)
Audience number 65 starts watching the film_1!(count: 1)
Audience number 66 starts watching the film_1!(count: 2)
Audience number 71 starts watching the film_2!(count: 1)
Audience number 73 starts watching the film_3!(count: 1)
Audience number 68 starts watching the film_1!(count: 1)
Audience number 69 starts watching the film_1!(count: 2)
Audience number 70 starts watching the film_1!(count: 3)
Audience number 72 starts watching the film_2!(count: 1)
Audience number 74 starts watching the film_3!(count: 1)
Audience number 75 starts watching the film_1!(count: 1)
Audience number 79 starts watching the film_2!(count: 1)
Audience number 76 starts watching the film_3!(count: 1)
Audience number 77 starts watching the film_1!(count: 1)
Audience number 82 starts watching the film_2!(count: 1)
Audience number 81 starts watching the film_3!(count: 1)
Audience number 78 starts watching the film_1!(count: 1)
Audience number 80 starts watching the film_1!(count: 2)
Audience number 85 starts watching the film_2!(count: 1)
Audience number 83 starts watching the film_3!(count: 1)
Audience number 84 starts watching the film_1!(count: 1)
Audience number 88 starts watching the film_2!(count: 1)
Audience number 86 starts watching the film_3!(count: 1)
Audience number 89 starts watching the film_3!(count: 3)
Audience number 87 starts watching the film_3!(count: 2)
Audience number 92 starts watching the film_1!(count: 1)
Audience number 91 starts watching the film_2!(count: 1)
Audience number 90 starts watching the film_3!(count: 1)
Audience number 97 starts watching the film_1!(count: 1)
Audience number 93 starts watching the film_2!(count: 1)
Audience number 98 starts watching the film_2!(count: 3)
Audience number 96 starts watching the film_2!(count: 2)
Audience number 94 starts watching the film_3!(count: 1)
Audience number 99 starts watching the film_3!(count: 2)
Audience number 96 starts watching the film_3!(count: 3)
Audience number 104 starts watching the film_1!(count: 1)
Audience number 100 starts watching the film_2!(count: 1)
Audience number 102 starts watching the film_2!(count: 2)
Audience number 102 starts watching the film_3!(count: 1)
Audience number 103 starts watching the film_3!(count: 2)
Audience number 106 starts watching the film_1!(count: 1)
Audience number 105 starts watching the film_2!(count: 1)
Audience number 114 starts watching the film_3!(count: 1)
Audience number 107 starts watching the film_1!(count: 1)
Audience number 110 starts watching the film_1!(count: 2)
Audience number 111 starts watching the film_1!(count: 4)
...
*/