#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void *disp()
{
    printf("Process ID : %d\n",getpid());
    printf("Thread ID : %ld\n",pthread_self());
}

int main()
{
    pthread_t myThread;
    pthread_create(&myThread,NULL,disp,NULL);
    pthread_join(myThread,NULL);
    return 0;
}