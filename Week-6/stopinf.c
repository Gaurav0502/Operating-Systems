#include<stdio.h>
#include<stdlib.h>
#include <unistd.h> 
#include <assert.h>
#include<sys/wait.h>
#include<sys/types.h>

int main()
{
    int process_id = 0;
    printf("Enter the id of the process to be terminated :");
    scanf("%d",&process_id);
    kill(process_id,SIGINT);
    return 0;
}