#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 2

sem_t freeSlotsInWarehouse;
sem_t warehouseFull;

pthread_mutex_t mutexBuffer;

int warehouse[10];
int count = 0;

void* producer(void* args) {
    while (1) 
    {
        // Produce
        int x = rand() % 100;
        sleep(1);


        // Add to the warehouse
        sem_wait(&freeSlotsInWarehouse);
        pthread_mutex_lock(&mutexBuffer);
        
        printf("Producer : Produced %d\n",x);

        warehouse[count] = x;
        count++;


        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&warehouseFull);
    }
}

void* consumer(void* args) {
    while (1) {
        int y;

        // Remove from the warehouse
        sem_wait(&warehouseFull);
        pthread_mutex_lock(&mutexBuffer);
        y = warehouse[count - 1];
        count--;
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&freeSlotsInWarehouse);

        // Consume
        printf("Consumer : Consumed %d\n", y);
        sleep(1);
    }
}

int main(int argc, char* argv[]) 
{
    srand(time(NULL));
    pthread_t th[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&freeSlotsInWarehouse, 0, 10);
    sem_init(&warehouseFull, 0, 0);
    int i;
    for (i = 0; i < THREAD_NUM; i++) 
    {
        if (i > 0) 
        {
            if (pthread_create(&th[i], NULL, &producer, NULL) != 0) 
            {
                perror("Failed to create thread");
            }
        }
        else 
        {
            if (pthread_create(&th[i], NULL, &consumer, NULL) != 0) 
            {
                perror("Failed to create thread");
            }
        }
    }
    for (i = 0; i < THREAD_NUM; i++) 
    {
        if (pthread_join(th[i], NULL) != 0) 
        {
            perror("Failed to join thread");
        }
    }
    sem_destroy(&freeSlotsInWarehouse);
    sem_destroy(&warehouseFull);
    pthread_mutex_destroy(&mutexBuffer);
    return 0;
}