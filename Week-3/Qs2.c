#include <stdlib.h>
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

long factorial(int n)
{
    long f = 1;
    for(int i = 1;i <= n;i++)
    {
        f *= i;
    }
    return f;
}

void fibonacci(int n)
{
     int n1=0,n2=1,n3,i;  
     printf("%d %d",n1,n2);  
     for(i=2;i<n;++i)  
     {    
       n3=n1+n2;    
       printf(" %d",n3);    
       n1=n2;    
       n2=n3;    
     }  
}

int main()
{
	pid_t pid = vfork();
	if (pid == 0)
		{
		    printf("Child is calculating factorial....\n");
            printf("Enter a number n : ");
            int n;
            scanf("%d",&n);
            printf("Factorial of n : %ld\n",factorial(n));
        }
	else		
		{
			printf("Parent is printing fibonacci series....\n");
            printf("Enter a number of terms 'n': ");
            int n;
            scanf("%d",&n);
            fibonacci(n);
            printf("\n");
            exit(0);
		}

	return 0;
}