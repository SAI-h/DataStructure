/*
理发店有一位理发师、一把理发椅和n把供等候理发的顾客坐的椅子.若没有顾客,理发师便在理发椅上睡觉,
一位顾客到来时,顾客必须叫醒理发师,若理发师正在理发时又有顾客来到,若有空椅子可坐,则坐下来等待,否则就离开.
试用pv操作实现并说明信号量的定义和初值.

这种解法没有考虑周全,理发师在理发时是用专门的理发座位的,顾客在没有人其他人在理发时,就直接可以去理发了,
不必占用一个等候的座位(?是吗).还有题目中的叫醒理发师,可以理解为唤醒理发师进程.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t seats; // 座位
sem_t waitingCount; // 等候人数
sem_t op1; // 保证加入等待队列的操作是原子操作
sem_t op2; // 保证理发操作是互斥的

int n, m;
int *waitingQueue; // 等候队列
int front = 0, rear = 0; // 队头以及队尾指针
int value_1, value_2; // 信号量seats、waitingcount的值

void *barber(void *arg) {
    while(1) {
        sem_getvalue(&waitingCount, &value_2);
        if(value_2) {
            sem_wait(&waitingCount);
            sem_wait(&op2);
            int id = waitingQueue[front];
            front = (front + 1) % n;
            printf("The barber is going to cut customer %d's hair!\n", id);
            sem_post(&op2);
            sem_post(&seats);
            printf("Finished the customer's haircut work, and Customer %d left the barber shoop!\n", id); 
        }else { // 没有人等着理发,理发师休息
            printf("The barber is resting!\n");
        }
    }
}

void *customer(void *arg) {
    int id = *(int *)arg;
    sem_getvalue(&seats, &value_1);
    if(value_1) { // 有座位等候理发
        sem_wait(&seats);
        printf("Customer %d is waiting for a haircut!\n", id);
        // 将顾客加入等候队列,等待理发师调度
        sem_wait(&op1);
        waitingQueue[rear] = id;
        rear = (rear + 1) % n;
        sem_post(&op1);
        sem_post(&waitingCount);
    }else { // 没有座位了,直接离开
        printf("Customer %d left the barber shoop!\n", id);
    }
}

int main(void) {
    printf("Please input the number of seats for rest:");
    scanf("%d", &n);
    printf("Please input the number of customers:");
    scanf("%d", &m);
    sem_init(&seats, 0, n);
    sem_init(&waitingCount, 0, 0);
    sem_init(&op1, 0, 1);
    sem_init(&op2, 0, 1);
    waitingQueue = (int *)malloc(sizeof(int) * (n + 1));
    pthread_t tid[1 + m];
    pthread_create(tid, NULL, barber, NULL);
    for(int i = 1; i <= m; i ++) pthread_create(tid + i, NULL, customer, &i); 
    for(int i = 0; i < 1 + m; i ++) pthread_join(tid[i], NULL);
    return 0;
}