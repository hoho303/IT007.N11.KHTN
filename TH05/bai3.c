#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include"pthread.h"
#include<time.h>

#define n 100
sem_t sem1;
sem_t sem2;

int x = 0;

void *processA(void *arg){
    while(1){
        x = x + 1;
        _sleep(0.5);
        if (x == 20) x = 0;
        printf("%d\n", x);
    }
}

void *processB(void *arg){
    while(1){
        x = x + 1;
        _sleep(0.5);
        if (x == 20) x = 0;
        printf("%d\n", x);
    }
}

int main()
{
    pthread_t tid1, tid2;
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);
    pthread_create(&tid1, NULL, processA, NULL);
    pthread_create(&tid2, NULL, processB, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}
