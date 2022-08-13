/*
设公共汽车上驾驶员和售票员的活动分别为--驾驶员:启动车辆、正常行车、到站停车;售票员:关车门、售票、开车门.
在汽车不断地到站、停车、行驶的过程中,试用pv操作调节二者的同步关系.
*/

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include <semaphore.h>

sem_t door_close, bus_stop;

void *driver(void *arg) {
    while(1) {
        sem_wait(&door_close);
        printf("driver: Vehicle launch!\n");
        printf("driver: Vehicle in motion!\n");
        printf("driver: Arrived at the station!\n");
        sem_post(&bus_stop);
        // usleep(1000 * 1000 / 20);
    }
}

void *conductor(void *arg) {
    while(1) {
        printf("conductor: Close the door!\n");
        sem_post(&door_close);
        printf("conductor: Sale the tickets!\n");
        sem_wait(&bus_stop);
        printf("conductor: Open the door!\n");
        // usleep(1000 * 1000 / 20);
    }
}

int main(void) {
    sem_init(&door_close, 0, 0);
    sem_init(&bus_stop, 0, 0);
    pthread_t tid[2];
    pthread_create(&tid[0], NULL, driver, NULL);
    pthread_create(&tid[1], NULL, conductor, NULL);
    for(int i = 0; i < 2; i ++) pthread_join(tid[i], NULL);
    return 0;
}