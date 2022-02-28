#include <sys/time.h> 
#include<stdio.h>
#include <unistd.h> 
#include <assert.h>

long nanosec(struct timeval t)
{ 
  return((t.tv_sec*1000000+t.tv_usec)*1000); 
}


long findEvens(long n)
{
    int e = 0;
    for(int i = 0;i < n;i++)
    {
        if(n%2 == 0)
        {
            e++;
        }
    }
}

int main()
{ 
  int res; 
  int N = 1000;
  float avgTimeSysCall,avgTimeFact,avgTimeFile,avgTimeFunc; 
  struct timeval t1, t2;
  res=gettimeofday(&t1,NULL); 
  assert(res==0); 
  for (int i=0;i< N; i++)
  { 
    int j = getppid();
  } 
  res=gettimeofday(&t2,NULL);   
  assert(res==0); 
  avgTimeSysCall = (nanosec(t2) - nanosec(t1))/(N*1.0);

  //Computing factorial of N
  res=gettimeofday(&t1,NULL);  
  assert(res==0); 
  long f = 1;
  for(int j = 1;j <= N;j++)
  {
    f *= j;
  } 
  res=gettimeofday(&t2,NULL);   
  assert(res==0); 
  avgTimeFact = (nanosec(t2) - nanosec(t1))/(N*1.0); 

  res=gettimeofday(&t1,NULL);  
  assert(res==0); 
  findEvens(N);
  res=gettimeofday(&t2,NULL);   assert(res==0); 
  avgTimeFunc = (nanosec(t2) - nanosec(t1))/(N*1.0);

  //File opening and processing
  res=gettimeofday(&t1,NULL); 
  assert(res==0); 
  FILE *fptr;
  char ch[50];
  int vc = 0;
  fptr = fopen("sample.txt","r");
  fscanf(fptr,"%s",ch);
  //Counting the number of vowels 
  //in the first word in the file.
  for(int i = 0;i < 50;i++)
  {
    if(ch[i]=='a' || ch[i]=='e' || ch[i]=='i' || ch[i]=='o' || ch[i]=='u')
    {
      vc++;
    }
  }
  res=gettimeofday(&t2,NULL);   
  assert(res==0); 
  avgTimeFile = (nanosec(t2) - nanosec(t1))/(N*1.0);

  printf("Average time for System call getpid : %f\n",avgTimeSysCall); 
  printf("Average time for Factorial Computation : %f\n",avgTimeFact); 
  printf("Average time for Function Computation : %f\n",avgTimeFunc); 
  printf("Average time for File opening and processing Computation(System call+Procedural Call) : %f\n",avgTimeFile);
}
