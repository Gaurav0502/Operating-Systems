#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t wrt;
pthread_mutex_t mutex;

int sum = 1;
int numreader = 0;

void *writer()
{   
    sem_wait(&wrt);

    sum = sum + 2;

    printf("Writer : wrote sum as : %d\n",sum);
    
    sem_post(&wrt);

}
void *reader(void *rno)
{   
    pthread_mutex_lock(&mutex);
    numreader++;
    if(numreader == 1) 
    {
        sem_wait(&wrt);
    }
    pthread_mutex_unlock(&mutex);
    printf("Reader : read sum as : %d\n",sum);

    pthread_mutex_lock(&mutex);
    numreader--;
    if(numreader == 0) 
    {
        sem_post(&wrt);
    }
    pthread_mutex_unlock(&mutex);
}

int main()
{   

    pthread_t read[5],write[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&wrt,0,1);

    for(int i = 1;i <= 10;i++)
    {
        if(i % 2 == 0)
        {
           pthread_create(&read[(int)i/2 - 1], NULL, (void *)reader,NULL);
        }
        else
        {
           pthread_create(&write[(int)i/2], NULL, (void *)writer,NULL);
        }
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&wrt);

    return 0;
    
}