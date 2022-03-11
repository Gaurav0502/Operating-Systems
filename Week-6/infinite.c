#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include <assert.h>
#include<sys/wait.h>
#include<sys/types.h>

void sighandler(int n)
{
   if(n == SIGINT)
   {
       printf("Received the signal...Program has terminated!!\n");
       exit(0);
   }
   else
   {
       printf("Received %d signal..",n);
   }
}

int main()
{
    void (*sigHandlerReturn)(int);
    sigHandlerReturn = signal(SIGINT, sighandler);
    for(;;)
    {
        printf("%d\n",getpid());
        sleep(1);
    }
    return 0;
}