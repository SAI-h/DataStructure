/*
三个合作进程,都需要从同一个设备输入各自的数据a、b、c,该输入设备需要互斥使用,
而且第一个数据必须由P1进程读取,第二个数据必须由P2进程读取,第三个数据必须由P3进程读取.
然后三个进程分别进行下面的计算:
P1: x = a + b;
P2: y = a * b;
P3: z = y + c - a;
最后,P1进程通过所连接的打印机将计算结果x,y,z的值打印出来.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

int a, b, c, x, y, z;
sem_t s1, s2, s3; // s1、s2、s3同步输入,s1也被用作同步输出
sem_t sb, sy; // 判定b变量是否被输入的信号量,以及y变量是否完成计算的信号量

void *P1(void *arg) {
    sem_wait(&s1);
    printf("Please input the value of a:");
    scanf("%d", &a);
    sem_post(&s2);

    sem_wait(&sb); // P1对a的输入在P2对b的输入之前,而P1中x的计算是由a、b两个变量共同决定的,
                   // 在当前语句阶段a已经完成了输入,因此P1进程需要等待P2进程对b的输入之后才可以进行计算
    x = a + b;

    sem_wait(&s1); // 在当前语句下,x的计算操作已经完成,s1的唤醒是由P3进行的,
                   // 就是说P3完成了对z的计算,而z的计算时在y的计算完成的基础上的,因此P2早于P3完成了对y的计算
                   // 所以当前状态下,x、y、z已经被全部计算出来，可以进行输出操作
    printf("x = %d, y = %d, z = %d\n", x, y, z);
}

void *P2(void *arg) {
    sem_wait(&s2);
    printf("Please input the value of b:");
    scanf("%d", &b);
    sem_post(&sb); // 告知P1进程,b的值的输入完成了
    sem_post(&s3);

    y = a * b; // 再b的值被输入后,当前已经完成了对a、b的输入,则P2进程可以直径进行计算,不需要等待
    sem_post(&sy); // 告知P3进程y值完成了计算
}

void *P3(void *arg) {
    sem_wait(&s3);
    printf("Please input the value of c:");
    scanf("%d", &c);
    
    sem_wait(&sy); // P3进程中对z值的计算,需要y、c、a三个变量,其中a的输入最先完成的,而且在当前语句下已经完成了对c变量的输入
                   // 因此对于此时的P3进程而言,他所急需的是y的值,即需要等待y值被计算出来,才能计算z值
    z = y + c - a;
    sem_post(&s1); // 告知P1进程可以开始打印信息的操作
}

int main(void) {
    sem_init(&s1, 0, 1);
    sem_init(&s2, 0, 0);
    sem_init(&s3, 0, 0);
    sem_init(&sb, 0, 0);
    sem_init(&sy, 0, 0);
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, P1, NULL);
    pthread_create(&tid[1], NULL, P2, NULL);
    pthread_create(&tid[2], NULL, P3, NULL);
    for(int i = 0; i < 3; i ++) pthread_join(tid[i], NULL);
    return 0;
}