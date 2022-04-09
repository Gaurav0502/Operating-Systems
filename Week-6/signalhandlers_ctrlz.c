#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include <assert.h>
#include<sys/wait.h>
#include<sys/types.h>

void sighandler(int n)
{
  if(n == SIGTSTP)
  {
       printf("You have pressed CTRL - Z.\n");
       exit(0);
  }

}

int main()
{
    void (*sigHandlerReturn)(int);
    sigHandlerReturn = signal(SIGTSTP, sighandler);

    for(;;)
    {
       printf("Press CTRL-Z to exit this infinite loop..\n");
       //added to reduce the rate of output
       //being printed in the terminal.
       sleep(2);
    }
    
    return 0;
}