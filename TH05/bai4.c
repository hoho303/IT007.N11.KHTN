#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include"pthread.h"
#include<time.h>

int x = 0;
pthread_mutex_t mutex;

void *processA(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        x = x + 1;
        _sleep(0.5);
        if (x == 20) x = 0;
        printf("%d\n", x);
        pthread_mutex_unlock(&mutex);
        }
}

void *processB(void *arg){
    while(1){
        pthread_mutex_lock(&mutex);
        x = x + 1;
        _sleep(0.5);
        if (x == 20) x = 0;
        printf("%d\n", x);
        pthread_mutex_unlock(&mutex);
    }
}

void main()
{
    pthread_t tid1, tid2;

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&tid1, NULL, processA, NULL);
    pthread_create(&tid2, NULL, processB, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;
}