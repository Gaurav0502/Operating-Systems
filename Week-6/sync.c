#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include <assert.h>
#include<sys/wait.h>
#include<sys/types.h>

void sighandler(int n)
{
   if(n == SIGCHLD)
   {
       printf("Parent Process received the signal from the child process\n");
       printf("Process %d has terminated!\n",getpid());
       exit(0);
   }
   else
   {
       printf("Received %d signal..",n);
   }
}

int sumofAP(int start,int common_difference,int end)
{
    int s = 0;
    for(int i = start;i <= end;i += common_difference)
    {
       s += i;
    }
    return s;
}

int main()
{
    int cid = fork();
    if(cid == 0)
    {
        //child process.
        printf("Child process %d is executing....\n",getpid());
        printf("Sum of AP with a = 5 and d = 10 upto 113 = %d\n",sumofAP(5,10,113));
        kill(getppid(),SIGCHLD);
    }
    else
    {
        struct sigaction sig;
        sigemptyset(&sig.sa_mask);
        sig.sa_flags = 0;
        sig.sa_handler = sighandler;
        sigaction(SIGCHLD,&sig,NULL);
        sleep(2);
    }
    printf("Process %d has terminated!\n",getpid());
    
    return 0;
}
