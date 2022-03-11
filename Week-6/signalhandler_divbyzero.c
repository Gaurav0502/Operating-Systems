#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include <assert.h>
#include<sys/wait.h>
#include<sys/types.h>

void sighandler(int n)
{
  if(n == SIGFPE)
  {
       printf("You have attempted to divide by 0.\n");
       exit(0);
  }

}

int main()
{
    void (*sigHandlerReturn)(int);
    sigHandlerReturn = signal(SIGFPE, sighandler);
    
    int a = 1/0;
 
    return 0;
}