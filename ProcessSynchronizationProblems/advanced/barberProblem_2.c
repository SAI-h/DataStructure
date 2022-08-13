/*
理发店有一位理发师、一把理发椅和n把供等候理发的顾客坐的椅子.若没有顾客,理发师便在理发椅上睡觉,
一位顾客到来时,顾客必须叫醒理发师,若理发师正在理发时又有顾客来到,若有空椅子可坐,则坐下来等待,否则就离开.
试用pv操作实现并说明信号量的定义和初值.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t hasCustomer; // 用于对理发师的唤醒
sem_t haircut; // 用于不同顾客之间对理发师征求的互斥访问
sem_t mutex; // 修改waitings的互斥信号量

int restSeats, numOfcustomers;
int waitings; // 坐在空椅子上等待的人

void *barber(void *arg) {
    while(1) {
        sem_wait(&hasCustomer);
        sem_wait(&mutex);
        waitings --; // 从等待的椅子上,坐到了理发的地方,空出来了一个位置
        sem_post(&mutex);
        printf("cut hair!\n");
        sem_post(&haircut); // 可以安排下一个理发了
    }
}

void *customer(void *arg) {
    sem_wait(&mutex);
    if(waitings < restSeats) { // 等待的人少于椅子的个数,有空椅子可以坐着等待
        waitings ++;
        sem_post(&mutex);
        sem_post(&hasCustomer); // 顾客进来了,唤醒理发师
        sem_wait(&haircut); // 多个顾客不能同时理发,因此这里需要互斥访问,可以理解为只有一个顾客可以理发,其他顾客在椅子上等待
        printf("get haircut!\n");
    }else {
        sem_post(&mutex);
        printf("customer leaving!\n");
    }
}

int main(void) {
    sem_init(&hasCustomer, 0, 0); // 初始时没有顾客,理发师在睡觉
    sem_init(&haircut, 0, 1);
    sem_init(&mutex, 0, 1);
    printf("Please input the number of seats for rest:");
    scanf("%d", &restSeats);
    printf("Please input the number of customers:");
    scanf("%d", &numOfcustomers);
    pthread_t tid[1 + numOfcustomers];
    pthread_create(tid, NULL, barber, NULL); // 在设置的时候将顾客的数量确定为一定值,因此最终稿结束时理发师会处于无顾客休息阻塞状态,故程序会停滞类似于发生了死锁
    for(int i = 1; i <= numOfcustomers; i ++) pthread_create(tid + i, NULL, customer, NULL);
    for(int i = 0; i <= numOfcustomers; i ++) pthread_join(tid[i], NULL);
    return 0;
}