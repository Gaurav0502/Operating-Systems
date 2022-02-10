#include <stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main()
{
	pid_t pid = fork();
	if (pid == 0)
		{
		    printf("Child Process ID : %d\n",getpid());
        }
	else		
		{
			printf("Parent Process ID : %d\n",getpid());
		}

	return 0;
}