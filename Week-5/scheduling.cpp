#include<iostream>
#include<stdio.h>
#include<vector>
#include<list>
#include<limits.h>
using namespace std;
#define T 2

class Premptive_Scheduling
{
   private:
     int n; 
     int **data,*burstcpy;
     int **output;
     vector<int> ganttChart; 
   public:
     double averageTurnAroundTime = 0;
     double averageWaitingTime = 0;
     
     //Sorting the given process data by the arrival time.
     //In ascending order.
     void sortByArrivalTime()
     {
         for(int i = 0;i < n;i++)
         {
             for(int j =  0; j < n;j++)
             {
                if(data[i][1] <= data[j][1])
                {
                    int* temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
             }
         }
     }

     //Sorting a part of the array based on given parameter.
     void sortByCriteria(int startIndex,int endIndex,int criteriaIndex)
     {
         for(int i = startIndex;i <= endIndex;i++)
         {
             for(int j =  startIndex; j <= endIndex;j++)
             {
                if(data[i][criteriaIndex] <= data[j][criteriaIndex])
                {
                    int* temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
             }
         }
         displayData();
     }

     int getIndex(int pid)
     {
         for(int i = 0;i < n;i++)
         {
             if(data[i][0] == pid)
             {
                 return i;
             }
         }
         return -1;
     }

     //Computes the average Wait Time.
     //and Turnaround Time.
     void computeAverage()
     {
        for(int i = 0;i < n;i++)
        {
            averageTurnAroundTime += output[i][1];
            averageWaitingTime += output[i][2];
        }

        averageTurnAroundTime /= n;
        averageWaitingTime /= n;

        printf("Average Turnaround Time = %f\n",averageTurnAroundTime);
        printf("Average Wait Time = %f\n",averageWaitingTime);
     }

   public:

     Premptive_Scheduling(int n)
     {
        this->n = n;
        data = new int*[n];
        output = new int*[n];
        burstcpy = new int[n];
        for(int i = 0;i < n;i++)
        {
            data[i] = new int[4];
            output[i] = new int[3];
        }
     }

     //Displays the computed parameters.
     void displayOutput()
     {
         printf("CT\tTAT\tWT\n");
         for(int i = 0;i < n;i++)
         {
            printf("%d\t%d\t%d\n",output[i][0],output[i][1],output[i][2]);
         }
     }

     //Displays the given process data.
     void displayData()
     {
         printf("PID\tAT\tBT\tPriority\n");
         for(int i = 0;i < n;i++)
         {
            printf("%d\t%d\t%d\t%d\n",data[i][0],data[i][1],data[i][2],data[i][3]);
         }
     }

     //Computing the sum of an array.
     int sum(int a[])
     {
         int s = 0;
         for(int i = 0;i < n;i++)
         {
            s += a[i];
         }
         return s;
     }

     //Inputs the given process data.
     void getData()
     {
         for(int i = 0;i < n;i++)
         {
             scanf("%d %d %d %d",&data[i][0],&data[i][1],&data[i][2],&data[i][3]);
             burstcpy[i] = data[i][2];
         }
         displayData();
     }

     //Function for Short Job Remaining Scheduling First Algorithm.
     void SJRF()
     {
         sortByArrivalTime();
         int time = sum(burstcpy);
         printf("Time  = %d\n",time);
         
         for(int i = 0;i < time;i++)
         {
             int minBurstTime = INT_MAX; 
             int minBurstTimeIndex = 0;
 
             //printf("Entered1\n");

             for(int j = 0;j < n;j++)
             {
                 //printf("Entered2\n");
                 if((data[j][2] != 0) && (data[j][1] <= i) && (data[j][2] < minBurstTime))
                 {
                     minBurstTime = data[j][2];
                     minBurstTimeIndex = j;
                 }
             }

             data[minBurstTimeIndex][2]--;
             ganttChart.push_back(data[minBurstTimeIndex][0]);

             displayData();
         }

        for(int i = 0;i < time;i++)
        {
            for(int j = 0;j < n;j++)
            {
                if(ganttChart.at(i) == (j + 1))
                {
                    printf("Last Executed(Time = %d) : %d\n",i,j+1);
                    output[j][0] = i + 1;
                    output[j][1] = output[j][0] - data[j][1];
                    output[j][2] = output[j][1] - burstcpy[j];
                }
            }
        }
         
         computeAverage();
         displayOutput();
        
     }

     //Function for Pre-Emptive Priority Scheduling Algorithm.
     void priorityPreEmptive()
     {
         sortByArrivalTime();
         int time = sum(burstcpy);
         printf("Time  = %d\n",time);
         
         for(int i = 0;i < time;i++)
         {
             int minPriority = INT_MAX; 
             int minPriorityIndex = 0;
 
             //printf("Entered1\n");

             for(int j = 0;j < n;j++)
             {
                 //printf("Entered2\n");
                 if((data[j][2] != 0) && (data[j][1] <= i) && (data[j][3] < minPriority))
                 {
                     minPriority = data[j][3];
                     minPriorityIndex = j;
                 }
             }

             data[minPriorityIndex][2]--;
             ganttChart.push_back(data[minPriorityIndex][0]);

             //displayData();
         }

        for(int i = 0;i < time;i++)
        {
            for(int j = 0;j < n;j++)
            {
                if(ganttChart.at(i) == (j + 1))
                {
                    //printf("Last Executed(Time = %d) : %d\n",i,j+1);
                    output[j][0] = i + 1;
                    output[j][1] = output[j][0] - data[j][1];
                    printf("CT = %d AT = %d\n",output[j][0],data[j][1]);
                    output[j][2] = output[j][1] - burstcpy[j];
                }
            }
        }
         
         computeAverage();
         displayOutput();
      
     }

     //Function for Round Robin Scheduling Algorithm.
     void roundRobin()
     {
         sortByArrivalTime();
         list<int> readyQueue;
         vector<int> timeline;
         readyQueue.push_back(0);
         int count = 0;

         for(int time = 0;time < sum(burstcpy);)
         {
            int currentProcess = readyQueue.front();
            readyQueue.pop_front();
           if(data[currentProcess][2] >= T)
           {
             data[currentProcess][2] -= T;
             time += T;
           }
           else
           {
             time += data[currentProcess][2];
             data[currentProcess][2] = 0;
           }
            ganttChart.push_back(data[currentProcess][0]);
            timeline.push_back(time);
         if(count < n - 1)
         { 
            for(int i = currentProcess + 1;i < n;i++)
            {
                if(data[i][1] <= time && data[i][2] > 0)
                {
                    count++;
                    readyQueue.push_back(i);
                }
                else
                {
                    break;
                }
            }
         }
            
            if(data[currentProcess][2] > 0)
            {
                readyQueue.push_back(currentProcess);
            }

            displayData();
        }

        for(int i = 0;i < ganttChart.size();i++)
        {
            for(int j = 0;j < n;j++)
            {
                if(ganttChart.at(i) == j + 1)
                {
                    //printf("Last Executed(Time = %d) : %d\n",timeline.at(i),j + 1);
                    output[j][0] = timeline.at(i);
                    output[j][1] = output[j][0] - data[j][1];
                    output[j][2] = output[j][1] - burstcpy[j];
                }
            }
        }
         
        displayOutput();
        computeAverage();
     }
};

class Non_Premptive_Scheduling
{
    private:
     int n; 
     int **data;
     int **output;
    public:
     double averageTurnAroundTime = 0;
     double averageWaitingTime = 0;

     //Sorting the given process data by the arrival time.
     //In ascending order.
     void sortByArrivalTime()
     {
         for(int i = 0;i < n;i++)
         {
             for(int j =  0; j < n;j++)
             {
                if(data[i][1] <= data[j][1])
                {
                    int* temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
             }
         }
     }

     //Sorting a part of the array based on given parameter.
     void sortByCriteria(int startIndex,int endIndex,int criteriaIndex)
     {
         for(int i = startIndex;i <= endIndex;i++)
         {
             for(int j =  startIndex; j <= endIndex;j++)
             {
                if(data[i][criteriaIndex] <= data[j][criteriaIndex])
                {
                    int* temp = data[i];
                    data[i] = data[j];
                    data[j] = temp;
                }
             }
         }
         displayData();
     }
     
     //Computes the average Wait Time.
     //and Turnaround Time.
     void computeAverage()
     {
        for(int i = 0;i < n;i++)
        {
            averageTurnAroundTime += output[i][1];
            averageWaitingTime += output[i][2];
        }

        averageTurnAroundTime /= n;
        averageWaitingTime /= n;

        printf("Average Turnaround Time = %f\n",averageTurnAroundTime);
        printf("Average Wait Time = %f\n",averageWaitingTime);
     }
    
    public :
     Non_Premptive_Scheduling(int n)
     {
        this->n = n;
        data = new int*[n];
        output = new int*[n];
        for(int i = 0;i < n;i++)
        {
            data[i] = new int[4];
            output[i] = new int[3];
        }
     }

     //Inputs the given process data.
     void getData()
     {
         for(int i = 0;i < n;i++)
         {
             scanf("%d %d %d %d",&data[i][0],&data[i][1],&data[i][2],&data[i][3]);
         }
         displayData();
     }

     //Displays the given process data.
     void displayData()
     {
         printf("PID\tAT\tBT\tPriority\n");
         for(int i = 0;i < n;i++)
         {
            printf("%d\t%d\t%d\t%d\n",data[i][0],data[i][1],data[i][2],data[i][3]);
         }
     }

     //Displays the computed parameters.
     void displayOutput()
     {
         printf("CT\tTAT\tWT\n");
         for(int i = 0;i < n;i++)
         {
            printf("%d\t%d\t%d\n",output[i][0],output[i][1],output[i][2]);
         }
     }

     //Function for First Come First Serve Scheduling Algorithm.
     void FCFS()
     {
         sortByArrivalTime();
         displayData();
         int time = data[0][1];
         for(int i = 0;i < n;)
         {  
            if(data[i][1] <= time)
            {
               time += data[i][2];
               output[i][0] = time;
               output[i][1] = time - data[i][1];
               output[i][2] = output[i][1] - data[i][2];
               i++;
            }
            else
            {
                time += 1;
            }
         }
         displayOutput();
         computeAverage();
     }
    
     //Function for Shortest Job First Scheduling Algorithm.
     void SJF()
     {
         int end = 0;
         sortByArrivalTime();
         displayData();
         int time = 0;
         for(int i = 0;i < n;)
         {  
            if(data[i][1] <= time)
            {
               time += data[i][2];
               output[i][0] = time;
               output[i][1] = time - data[i][1];
               output[i][2] = output[i][1] - data[i][2];
               i++;
            }
            else
            {
                time += 1;
            }
            
          if(end != n-1)
          {
            for(int j = i + 1;j < n;j++)
            {
                if(data[i][1] > time)
                {
                   break;
                }
                else
                {
                    end = j;
                }
            }
            printf("End = %d\n",end);
            sortByCriteria(i,end,2);
          }
         }
         displayOutput();
         computeAverage();
     }

    //Function for Non-Pre Emptive Priority Scheduling Algorithm. 
     void priorityNonPreEmptive()
     {
         int end = 0;
         sortByArrivalTime();
         displayData();
         int time = 0;
         for(int i = 0;i < n;)
         {  
            if(data[i][1] <= time)
            {
               time += data[i][2];
               output[i][0] = time;
               output[i][1] = time - data[i][1];
               output[i][2] = output[i][1] - data[i][2];
               i++;
            }
            else
            {
                time += 1;
            }
            
          if(end != n-1)
          {
            for(int j = i + 1;j < n;j++)
            {
                if(data[i][1] > time)
                {
                   break;
                }
                else
                {
                    end = j;
                }
            }
            printf("End = %d\n",end);
            sortByCriteria(i,end,3);
          }
         }
         displayOutput();
         computeAverage();
     }
};

int main()
{
    double wt[6] = {13.8,16.56,14.512,4.6,5.52,9.6};
    string algos[6] = {"FCFS","Non-premptive priority","SJF","SRJF","Premptive Priority","Round Robin"};

    int min = INT_MAX;
    int in = 0;
    for(int i = 0;i < 6;i++)
    {
        if(wt[i] < min)
        {
           min = wt[i];
           in = i;
        }
    }

    cout<<algos[in]<<" gives least wait time of "<<wt[in]<<endl;

    return 0;
}