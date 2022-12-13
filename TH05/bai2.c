#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include"pthread.h"
#include<time.h>

#define n 100

sem_t sem1, sem2;

int a[n];
int i = 0;

void removeElement(int index)
{
    int j;
    for(j = index; j < i; j++)
    {
        a[j] = a[j+1];
    }
}

void *processA(void *arg)
{
    while(1)
    {
        sem_wait(&sem1);
        int k = rand() % 100;
        printf("Them phan tu %d vao mang a \n", k);
        a[i] = k;
        i++;
        printf("So phan tu trong mang a: %d \n", i);
        printf("\n");
        
        sem_post(&sem2);
    }
}

void *processB(void *arg)
{
    while(1)
    {
        sem_wait(&sem2);
        i--;
        if(i > 0)
        {
            removeElement(rand() % i);
            printf("So phan tu trong mang a: %d \n", i);
        }
        else
        {
            printf("### Nothing in array a \n");
        }
        printf("\n");
        sem_post(&sem1);
    }
}

int main()
{
    pthread_t tid1, tid2;
    sem_init(&sem1, 0, 3);
    sem_init(&sem2, 0, 0);

    pthread_create(&tid1, NULL, processA, NULL);
    pthread_create(&tid2, NULL, processB, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}
