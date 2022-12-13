#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include"pthread.h"
#include<time.h>

int x1 = 1, x2 = 2, x3 = 3, x4 = 4, x5 = 5, x6 = 6;
int w = 0, y = 0, v = 0, z = 0, ans = 0;

sem_t sem_AB, sem_CD, sem_EF, sem_G, sem_CDs, sem_EFs ,busy;

void *processAB(void *arg)
{
    while (1)
    {
        sem_wait(&sem_G);
        sem_wait(&busy);
        w = x1 * x2;
        v = x3 * x4;
        printf("w = x1*x2 = %d \n", w);
        printf("v = x3*x4 = %d \n", v);
        sem_post(&sem_AB);
        sem_post(&sem_CDs);
        sem_post(&busy);
    }
} 

void *processCD(void *args)
{
    while (1)
    {
        sem_wait(&sem_CDs);
        sem_wait(&sem_AB);
        sem_wait(&busy);
        y = v * x5;
        z = v * x6;
        printf("y = v*x5 = %d \n", y);
        printf("z = v*x6 = %d \n", z);
        sem_post(&sem_AB);
        sem_post(&sem_CD);
        sem_post(&sem_EFs);
        sem_post(&busy);
    }
}

void *processEF(void *args)
{
    while (1)
    {
        sem_wait(&sem_EFs);
        sem_wait(&sem_CD);
        sem_wait(&sem_AB);
        sem_wait(&busy);
        y = w * y;
        z = w * z;
        printf("y = w*y = %d \n", y);
        printf("z = w*z = %d \n", z);
        sem_post(&sem_EF);
        sem_post(&sem_EF);
        sem_post(&busy);
    }
}

void *processG(void *args)
{
    while (1)
    {
        sem_wait(&sem_EF);
        sem_wait(&busy);
        ans = y + z;
        printf("ans = y + z = %d \n", ans);
        sem_post(&sem_G);
        sem_post(&busy);
    }
}

int main()
{
    pthread_t tid1, tid2, tid3, tid4;

    sem_init(&sem_AB, 0, 0);
    sem_init(&sem_CD, 0, 0);
    sem_init(&sem_EF, 0, 0);
    sem_init(&sem_G, 0, 1);
    sem_init(&sem_CDs, 0, 0);
    sem_init(&sem_EFs, 0, 0);
    sem_init(&busy, 0, 1);

    pthread_create(&tid1, NULL, processA, NULL);
    pthread_create(&tid2, NULL, processCD, NULL);
    pthread_create(&tid3, NULL, processEF, NULL);
    pthread_create(&tid4, NULL, processG, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);

    sem_destroy(&sem_AB);
    sem_destroy(&sem_CD);
    sem_destroy(&sem_EF);
    sem_destroy(&sem_G);
    sem_destroy(&sem_CDs);
    sem_destroy(&sem_EFs);
    sem_destroy(&busy);

    return 0;
}
