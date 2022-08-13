/*
苹果橘子问题
桌子上有一个盘子,每次只能放一个水果.爸爸专门向盘子中放苹果,妈妈专门向盘子中放橘子.
儿子专等吃盘子中的橘子,女儿专等吃盘子中的苹果.只有盘子为空时,爸爸或妈妈才可向盘子中放一个水果;
仅当盘子中有自己需要的水果时,儿子或女儿可以从盘子中取出.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t empty, apple, orange;

void *dad(void *arg) {
    while(1) {
        sem_wait(&empty);
        printf("Dad: Apple_put\n");
        sem_post(&apple);
        usleep(1000 * 1000 / 20);
    }
}

void *mom(void *arg) {
    while(1) {
        sem_wait(&empty);
        printf("Mom: Orange_put\n");
        sem_post(&orange);
        usleep(1000 * 1000 / 20);
    }
}

void *son(void *arg) {
    while(1) {
        sem_wait(&orange);
        printf("Son: Orange_eat\n");
        sem_post(&empty);
        usleep(1000 * 1000 / 20);
    }
}

void *daughter(void *arg) {
    while(1) {
        sem_wait(&apple);
        printf("Daughter: Apple_eat\n");
        sem_post(&empty);
        usleep(1000 * 1000 / 20);
    }
}

int main(void) {
    sem_init(&empty, 0, 1);
    sem_init(&apple, 0, 0);
    sem_init(&orange, 0, 0);
    pthread_t tid[4];
    pthread_create(&tid[0], NULL, dad, NULL);
    pthread_create(&tid[1], NULL, mom, NULL);
    pthread_create(&tid[2], NULL, son, NULL);
    pthread_create(&tid[3], NULL, daughter, NULL);
    for(int i = 0; i < 4; i ++) pthread_join(tid[i], NULL);
    return 0;
}

/*
Dad: Apple_put
Daughter: Apple_eat
Mom: Orange_put
Son: Orange_eat
Dad: Apple_put
Daughter: Apple_eat
Mom: Orange_put
Son: Orange_eat
Dad: Apple_put
Daughter: Apple_eat
Mom: Orange_put
Son: Orange_eat
Dad: Apple_put
Daughter: Apple_eat
Mom: Orange_put
Son: Orange_eat
...
*/