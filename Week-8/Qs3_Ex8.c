#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void *dispRegno(void* tno)
{
    for(int i = 0;i < 50;i++)
    {
        printf("20BAI1153\n");
    }
    
}

void *dispName(void* tno)
{
    for(int i = 0;i < 50;i++)
    {
        printf("Gaurav Pendharkar\n");
    }
    
}

int main()
{
    pthread_t regno,name;

    pthread_create(&regno,NULL,dispRegno,NULL);
    pthread_join(regno,NULL);
    pthread_create(&name,NULL,dispName,NULL);
    pthread_join(name,NULL);
    
    return 0;
}