/*
设自行车生产线上有一个箱子,其中有N个位置(N>=3),每个位置可存放一个车架或一个车轮,
又设有三名工人:
工人1:加工一个车架,车架放在箱中
工人2:加工一个车轮,车轮放在箱中
工人3:箱中取一个车架、箱中取两个个车轮,组装为一台车
实现这三个工人的工作
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t full_frame, empty_frame;
sem_t full_wheel, empty_wheel;
sem_t empty_box;

void *worker_1(void *arg) {
    while(1) {
        // produce frame
        sem_wait(&empty_frame); // 注意sem_wait(&empty_frame)和sem_wait(&empty_box)这两句话不能对调,
                                // 直观来想empty_box是对车架和车轮总数的管辖,而empty_wait仅仅是对车架的管辖.
                                // 如果empty_frame为0那么不能说明给定车架的资源已经北完全分配,这时候对总数资源的申请也肯定会驳回.
                                // 但如果先申请总数资源empty_box,再分配empty_frame,如果此时empty_frame为0,将总资源分配出去时系统是不知情的.
                                // 这意味着已经不能再去分配的车架,强行占用了车轮的一个总数资源,可能会引发死锁.
                                // 即假设sem_wait(&empty_box)先于sem_wait(&empty_frame)给出
                                // 若empty_box资源数剩余为1,执行语句后资源数剩余为0,而empty_frame资源数在一开始就已经为0
                                // 那么worker_1会在sem_wait(&empty_box)语句等待
                                // 若worker_3恰好运行到了sem_wait(&full_wheel)等待轮子资源,因为empty_frame=0,这意味着此时箱子中有n-2个车架,理论上留有2个给轮子的空位
                                // 因为在sem_wait(&empty_box)之前empty_box=1(剩余一个空位),且empty_frame=0(n-2个车架全部放入),这就说明当前有一个车轮(n-(n-2)-1=1)
                                // 但是worker_3是需要两个车轮才能完成组装,因此worker_3就会在第二次sem_wait(&full_wheel)阻塞等待worker_2对full_wheel资源的释放
                                // 但可惜的是再worker_1中对empty_box的wait操作使得其当前值为0,因此worker_2也无法完成将车轮放入的操作,在他的视野中这个空位被worker_1霸占了
                                // 至此三名worker全部陷入阻塞,产生了死锁
        sem_wait(&empty_box);
        printf("Worker_1 put the frame in the box!\n");
        sem_post(&full_frame);
    }
}

void *worker_2(void *arg) {
    while(1) {
        // produce wheel
        sem_wait(&empty_wheel);
        sem_wait(&empty_box);
        printf("Worker_2 put the wheel in the box!\n");
        sem_post(&full_wheel);
    }
}

void *worker_3(void *arg) {
    while(1) {
        sem_wait(&full_frame);
        printf("Worker_3 got a frame out of the box!\n");
        sem_post(&empty_frame);
        sem_post(&empty_box);

        sem_wait(&full_wheel);
        sem_wait(&full_wheel);
        printf("Worker_3 got two wheels out of the box!\n");
        sem_post(&empty_wheel);
        sem_post(&empty_wheel);
        sem_post(&empty_box);
        sem_post(&empty_box);

        printf("The worker finished the assembly!\n");
    }
}

int main(void) {
    int n;
    printf("Please input the capacty of the box:");
    scanf("%d", &n);
    sem_init(&full_frame, 0, 0);
    sem_init(&empty_frame, 0, n - 2); // 要空出两个位置给车轮,极端地想如果箱子满了而且里面放的全是车架没有车轮,
                                      // 那么worker_3将缺少进行组装的车轮而阻塞,worker_2因为箱子是满的、没有办法去放车轮而阻塞
                                      // 那么就会产生死锁,因此车架的放置应该保证车轮在取得最少量时也能使得整个系统周转,故最多分配n-2个存储资源,下面的车轮放置也同理

    sem_init(&full_wheel, 0, 0);
    sem_init(&empty_wheel, 0, n - 1);
    sem_init(&empty_box, 0, n);
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, worker_1, NULL);
    pthread_create(&tid[1], NULL, worker_2, NULL);
    pthread_create(&tid[2], NULL, worker_3, NULL);
    for(int i = 0; i < 3; i ++) pthread_join(tid[i], NULL);
    return 0;
}