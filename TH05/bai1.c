#include<stdio.h>
#include<stdlib.h>
#include<semaphore.h>
#include"pthread.h"

sem_t sem1, sem2;
int sells = 0;
int products = 0;

void *producer(void *arg)
{
    while(1)
    {
        sem_wait(&sem1);
        products++;
        printf("products: sells = %d, products = %d, max product = %d \n",sells, products, products-sells);
        sem_post(&sem2);
    }
}

void *consumer(void *arg)
{
    while(1)
    {
        sem_wait(&sem2);
        sells++;
        printf("sells: sells = %d, products = %d, max product = %d \n",sells, products, products-sells);
        sem_post(&sem1);
    }
}

int main()
{
    pthread_t tid1, tid2;

    // condition sells <= products <= sells + 11
    sem_init(&sem1, 0, 11);
    sem_init(&sem2, 0, 0);

    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&sem1);
    sem_destroy(&sem2);

    return 0;
}
