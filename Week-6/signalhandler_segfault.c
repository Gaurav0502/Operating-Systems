#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include <assert.h>
#include<sys/wait.h>
#include<sys/types.h>

void sighandler(int n)
{
  if(n == SIGSEGV)
  {
       printf("You have encountered a segmentation fault.\n");
       exit(0);
  }

}

int main()
{
    void (*sigHandlerReturn)(int);
    sigHandlerReturn = signal(SIGSEGV, sighandler);

    int* p1 = NULL;
    *p1 = 3;  
    return 0;
}