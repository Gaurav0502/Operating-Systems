#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void *disp(void* tno)
{
    printf("Hello World (Thread %d)\n",*((int *)tno));
}

int main()
{
    pthread_t myThreads[5];
    
    for(int i = 0;i < 5;i++)
    {
        pthread_create(&myThreads[i],NULL,disp,(void *)&i);
    }
    
    for(int i = 0;i < 5;i++)
    {
        pthread_join(myThreads[i],NULL);
    }
    
    return 0;
}