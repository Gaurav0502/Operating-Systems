#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
int main() {
    int status;
    int i;
    int flag = 0;
    printf("Parent Process ID: %d\n", getpid());
    for( i = 0; i < 3; i++ ) {
        if(flag == 0) 
        {
            if( fork() == 0 ) 
            {
                flag++;
                printf("Child Process No. %d Created with PID: %d and Parent's PID: %d\n",i+1,getpid(), getppid());
                if (2-i != 0)
                  sleep(2*(2-i));
            }
        }
    }
    sleep(1);
    wait(&status);
    printf("Process with PID = %d terminated!\n", getpid());
    sleep(5);
}