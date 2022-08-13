/*
在一个仓库中可以存放A和B两种产品,要求:
1.每次只能存入一种产品
2.A产品数量-B产品数量 < M
3.B产品数量-A产品数量 < N
其中M、N为正整数,试描述A、B入库过程

这道题如果用更直观的想法做是否可行呢?
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

int countA = 0, countB = 0; // 记录仓库中A、B的货物数量
sem_t A_in, B_in; // 控制A、B两种货物入库的信号量
sem_t opA, opB; // 互斥操作的信号量
int m, n; // m:A-B的上限值(-1), n:B-A的上限值(-1)
int Ban_A, Ban_B; // A、B两种货物是否处于禁止存放状态

void *productA(void *arg) {
    while(1) {
        sem_wait(&opA);
        if(Ban_A == 0 && countA + 1 - countB == m) { // A的入库使得到达了上限值,那么就阻塞
                                                    // Ban_A==0的条件保证只会阻塞一次,防止多个进程进入使得A_in的值削减为负数
            Ban_A = 1;
            sem_wait(&A_in);
        }
        sem_post(&opA);

        sem_wait(&A_in);
        countA ++; 
        printf("Put A into warehouse(countA = %d, countB = %d)!\n", countA, countB); // 这两条语句要先于对B的唤醒操作,不然B提前唤醒后切换,所得到的count仍是原来的值
        sem_wait(&opB); // 保证这是B的原子操作
        if(Ban_B) { // 如果B是处于阻塞状态的,那么此时新增的A一定使得不等式重新满足,B就能回到就绪态
            sem_post(&B_in); 
            Ban_B = 0;
        }
        sem_post(&opB);
        sem_post(&A_in);

        // usleep(1000 * 1000 / 20);
    }
}

void *productB(void *arg) {
    while(1) {
        sem_wait(&opB);
        if(Ban_B == 0 && countB + 1 - countA == n) { // B的入库使得到达了上限值,那么就阻塞,
                                                    // Ban_B==0的条件保证只会阻塞一次,防止多个进程进入使得B_in的值削减为负数
            Ban_B = 1;
            sem_wait(&B_in);
        }
        sem_post(&opB);

        sem_wait(&B_in);
        countB ++;
        printf("Put B into warehouse(countA = %d, countB = %d)!\n", countA, countB); // 这两条语句要先于对A的唤醒操作,不然A提前唤醒后切换,所得到的count仍是原来的值
        sem_wait(&opA); // 保证这是A的原子操作
        if(Ban_A) {  // 如果A是处于阻塞状态的,那么此时新增的B一定使得不等式重新满足,A就能回到就绪态
            sem_post(&A_in);
            Ban_A = 0;
        }
        sem_post(&opA);
        sem_post(&B_in);

        usleep(1000 * 1000 / 20);
    }
}

int main(void) {
    printf("Enter the upper limit M of A-B:");
    scanf("%d", &m);
    printf("Enter the upper limit N of B-A:");
    scanf("%d", &n);

    sem_init(&A_in, 0, 1);
    sem_init(&B_in, 0, 1);
    sem_init(&opA, 0, 1);
    sem_init(&opB, 0, 1);
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, productA, NULL);
    pthread_create(&tid[0], NULL, productB, NULL);
    for(int i = 0; i < 2; i ++) pthread_join(tid[0], NULL);
    
    return 0;
}

/*
这里有意用usleep放缓了B的生产速率,可以看见A-B的差值始终在10以下:
Enter the upper limit M of A-B:10
Enter the upper limit N of B-A:1
Put A into warehouse(countA = 1, countB = 0)!
Put A into warehouse(countA = 2, countB = 0)!
Put A into warehouse(countA = 3, countB = 0)!
Put A into warehouse(countA = 4, countB = 0)!
Put B into warehouse(countA = 4, countB = 1)!
Put A into warehouse(countA = 5, countB = 1)!
Put A into warehouse(countA = 6, countB = 1)!
Put A into warehouse(countA = 7, countB = 1)!
Put A into warehouse(countA = 8, countB = 1)!
Put A into warehouse(countA = 9, countB = 1)!
Put A into warehouse(countA = 10, countB = 1)!
Put B into warehouse(countA = 10, countB = 2)!
Put A into warehouse(countA = 11, countB = 2)!
Put B into warehouse(countA = 11, countB = 3)!
Put A into warehouse(countA = 12, countB = 3)!
Put B into warehouse(countA = 12, countB = 4)!
Put A into warehouse(countA = 13, countB = 4)!
Put B into warehouse(countA = 13, countB = 5)!
Put A into warehouse(countA = 14, countB = 5)!
Put B into warehouse(countA = 14, countB = 6)!
Put A into warehouse(countA = 15, countB = 6)!
Put B into warehouse(countA = 15, countB = 7)!
Put A into warehouse(countA = 16, countB = 7)!
Put B into warehouse(countA = 16, countB = 8)!
Put A into warehouse(countA = 17, countB = 8)!
Put B into warehouse(countA = 17, countB = 9)!
Put A into warehouse(countA = 18, countB = 9)!
Put B into warehouse(countA = 18, countB = 10)!
Put A into warehouse(countA = 19, countB = 10)!
Put B into warehouse(countA = 19, countB = 11)!
Put A into warehouse(countA = 20, countB = 11)!
Put B into warehouse(countA = 20, countB = 12)!
Put A into warehouse(countA = 21, countB = 12)!
Put B into warehouse(countA = 21, countB = 13)!
Put A into warehouse(countA = 22, countB = 13)!
Put B into warehouse(countA = 22, countB = 14)!
Put A into warehouse(countA = 23, countB = 14)!
Put B into warehouse(countA = 23, countB = 15)!
Put A into warehouse(countA = 24, countB = 15)!
Put B into warehouse(countA = 24, countB = 16)!
Put A into warehouse(countA = 25, countB = 16)!
Put B into warehouse(countA = 25, countB = 17)!
Put A into warehouse(countA = 26, countB = 17)!
Put B into warehouse(countA = 26, countB = 18)!
Put A into warehouse(countA = 27, countB = 18)!
Put B into warehouse(countA = 27, countB = 19)!
Put A into warehouse(countA = 28, countB = 19)!
Put B into warehouse(countA = 28, countB = 20)!
Put A into warehouse(countA = 29, countB = 20)!
Put B into warehouse(countA = 29, countB = 21)!
Put A into warehouse(countA = 30, countB = 21)!
Put B into warehouse(countA = 30, countB = 22)!
Put A into warehouse(countA = 31, countB = 22)!
Put B into warehouse(countA = 31, countB = 23)!
Put A into warehouse(countA = 32, countB = 23)!
Put B into warehouse(countA = 32, countB = 24)!
Put A into warehouse(countA = 33, countB = 24)!
Put B into warehouse(countA = 33, countB = 25)!
Put A into warehouse(countA = 34, countB = 25)!
Put B into warehouse(countA = 34, countB = 26)!
Put A into warehouse(countA = 35, countB = 26)!
Put B into warehouse(countA = 35, countB = 27)!
Put A into warehouse(countA = 36, countB = 27)!
Put B into warehouse(countA = 36, countB = 28)!
Put A into warehouse(countA = 37, countB = 28)!
Put B into warehouse(countA = 37, countB = 29)!
Put A into warehouse(countA = 38, countB = 29)!
Put B into warehouse(countA = 38, countB = 30)!
Put A into warehouse(countA = 39, countB = 30)!
Put B into warehouse(countA = 39, countB = 31)!
Put A into warehouse(countA = 40, countB = 31)!
Put B into warehouse(countA = 40, countB = 32)!
Put A into warehouse(countA = 41, countB = 32)!
Put B into warehouse(countA = 41, countB = 33)!
Put A into warehouse(countA = 42, countB = 33)!
Put B into warehouse(countA = 42, countB = 34)!
Put A into warehouse(countA = 43, countB = 34)!
Put B into warehouse(countA = 43, countB = 35)!
Put A into warehouse(countA = 44, countB = 35)!
Put B into warehouse(countA = 44, countB = 36)!
Put A into warehouse(countA = 45, countB = 36)!
Put B into warehouse(countA = 45, countB = 37)!
Put A into warehouse(countA = 46, countB = 37)!
Put B into warehouse(countA = 46, countB = 38)!
Put A into warehouse(countA = 47, countB = 38)!
Put B into warehouse(countA = 47, countB = 39)!
Put A into warehouse(countA = 48, countB = 39)!
Put B into warehouse(countA = 48, countB = 40)!
Put A into warehouse(countA = 49, countB = 40)!
Put B into warehouse(countA = 49, countB = 41)!
Put A into warehouse(countA = 50, countB = 41)!
Put B into warehouse(countA = 50, countB = 42)!
Put A into warehouse(countA = 51, countB = 42)!
Put B into warehouse(countA = 51, countB = 43)!
Put A into warehouse(countA = 52, countB = 43)!
Put B into warehouse(countA = 52, countB = 44)!
Put A into warehouse(countA = 53, countB = 44)!
Put B into warehouse(countA = 53, countB = 45)!
Put A into warehouse(countA = 54, countB = 45)!
Put B into warehouse(countA = 54, countB = 46)!
Put A into warehouse(countA = 55, countB = 46)!
Put B into warehouse(countA = 55, countB = 47)!
Put A into warehouse(countA = 56, countB = 47)!
Put B into warehouse(countA = 56, countB = 48)!
Put A into warehouse(countA = 57, countB = 48)!
Put B into warehouse(countA = 57, countB = 49)!
Put A into warehouse(countA = 58, countB = 49)!
Put B into warehouse(countA = 58, countB = 50)!
Put A into warehouse(countA = 59, countB = 50)!
Put B into warehouse(countA = 59, countB = 51)!
Put A into warehouse(countA = 60, countB = 51)!
Put B into warehouse(countA = 60, countB = 52)!
Put A into warehouse(countA = 61, countB = 52)!
Put B into warehouse(countA = 61, countB = 53)!
Put A into warehouse(countA = 62, countB = 53)!
Put B into warehouse(countA = 62, countB = 54)!
Put A into warehouse(countA = 63, countB = 54)!
Put B into warehouse(countA = 63, countB = 55)!
Put A into warehouse(countA = 64, countB = 55)!
Put B into warehouse(countA = 64, countB = 56)!
Put A into warehouse(countA = 65, countB = 56)!
Put B into warehouse(countA = 65, countB = 57)!
Put A into warehouse(countA = 66, countB = 57)!
Put B into warehouse(countA = 66, countB = 58)!
Put A into warehouse(countA = 67, countB = 58)!
Put B into warehouse(countA = 67, countB = 59)!
Put A into warehouse(countA = 68, countB = 59)!
Put B into warehouse(countA = 68, countB = 60)!
Put A into warehouse(countA = 69, countB = 60)!
Put B into warehouse(countA = 69, countB = 61)!
Put A into warehouse(countA = 70, countB = 61)!
Put B into warehouse(countA = 70, countB = 62)!
Put A into warehouse(countA = 71, countB = 62)!
Put B into warehouse(countA = 71, countB = 63)!
Put A into warehouse(countA = 72, countB = 63)!
Put B into warehouse(countA = 72, countB = 64)!
Put A into warehouse(countA = 73, countB = 64)!
Put B into warehouse(countA = 73, countB = 65)!
Put A into warehouse(countA = 74, countB = 65)!
Put B into warehouse(countA = 74, countB = 66)!
Put A into warehouse(countA = 75, countB = 66)!
Put B into warehouse(countA = 75, countB = 67)!
Put A into warehouse(countA = 76, countB = 67)!
Put B into warehouse(countA = 76, countB = 68)!
Put A into warehouse(countA = 77, countB = 68)!
Put B into warehouse(countA = 77, countB = 69)!
Put A into warehouse(countA = 78, countB = 69)!
Put B into warehouse(countA = 78, countB = 70)!
Put A into warehouse(countA = 79, countB = 70)!
Put B into warehouse(countA = 79, countB = 71)!
Put A into warehouse(countA = 80, countB = 71)!
Put B into warehouse(countA = 80, countB = 72)!
Put A into warehouse(countA = 81, countB = 72)!
Put B into warehouse(countA = 81, countB = 73)!
Put A into warehouse(countA = 82, countB = 73)!
Put B into warehouse(countA = 82, countB = 74)!
Put A into warehouse(countA = 83, countB = 74)!
Put B into warehouse(countA = 83, countB = 75)!
Put A into warehouse(countA = 84, countB = 75)!
Put B into warehouse(countA = 84, countB = 76)!
Put A into warehouse(countA = 85, countB = 76)!
Put B into warehouse(countA = 85, countB = 77)!
Put A into warehouse(countA = 86, countB = 77)!
Put B into warehouse(countA = 86, countB = 78)!
...
*/