/*吸烟者问题*/
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t finish; // 接受到吸烟者完成吸烟的信息
sem_t offer1, offer2, offer3; // 三种吸烟者需要的完成吸烟所需要的物质条件组合
int i = 0; // 当前供应的吸烟者编号

void *supplier(void *arg) {
    while(1) {
        if(i == 0) sem_post(&offer1);
        else if(i == 1) sem_post(&offer2);
        else sem_post(&offer3);
        printf("Offer%d prepared!\n", i + 1);
        i = (i + 1) % 3;
        sem_wait(&finish); // 不应该放在开头位置,因为一开始信号量finish的值为0,标识三位吸烟者未完成(开始)吸烟,放在供应商会被阻塞,无法再去供应了
        usleep(1000 * 1000 / 20);
    }
}

void *smoker_1(void *arg) {
    while(1) {
        sem_wait(&offer1);
        printf("Smoker_1 fininshed!\n");
        sem_post(&finish);
        usleep(1000 * 1000 / 20);
    }
}

void *smoker_2(void *arg) {
    while(1) {
        sem_wait(&offer2);
        printf("Smoker_2 fininshed!\n");
        sem_post(&finish);
        usleep(1000 * 1000 / 20);
    }
}

void *smoker_3(void *arg) {
    while(1) {
        sem_wait(&offer3);
        printf("Smoker_3 fininshed!\n");
        sem_post(&finish);
        usleep(1000 * 1000 / 20);
    }
}

int main(void) {
    sem_init(&finish, 0, 0);
    sem_init(&offer1, 0, 0);
    sem_init(&offer2, 0, 0);
    sem_init(&offer3, 0, 0);
    pthread_t tid[4];
    pthread_create(&tid[0], NULL, supplier, NULL);
    pthread_create(&tid[1], NULL, smoker_1, NULL);
    pthread_create(&tid[2], NULL, smoker_2, NULL);
    pthread_create(&tid[3], NULL, smoker_3, NULL);
    for(int i = 0; i < 4; i ++) pthread_join(tid[i], NULL);
    return 0;
}

/*
Offer1 prepared!
Smoker_1 fininshed!
Offer2 prepared!
Smoker_2 fininshed!
Offer3 prepared!
Smoker_3 fininshed!
Offer1 prepared!
Smoker_1 fininshed!
Offer2 prepared!
Smoker_2 fininshed!
Offer3 prepared!
Smoker_3 fininshed!
Offer1 prepared!
Smoker_1 fininshed!
Offer2 prepared!
Smoker_2 fininshed!
Offer3 prepared!
Smoker_3 fininshed!
Offer1 prepared!
Smoker_1 fininshed!
Offer2 prepared!
Smoker_2 fininshed!
Offer3 prepared!
Smoker_3 fininshed!
Offer1 prepared!
Smoker_1 fininshed!
Offer2 prepared!
Smoker_2 fininshed!
Offer3 prepared!
Smoker_3 fininshed!
Offer1 prepared!
Smoker_1 fininshed!
...
*/