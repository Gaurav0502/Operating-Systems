#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

//Total Resources for the processes.
vector<int> resources;
//The safe sequence for preventing deadlock.
vector<int> safeSequence;
//The available resources after allotment to processes.
vector<int> available;

//Stores the process details.
class Process
{
   public:
    //Resources already alloted to process.
    vector<int> alloted;
    //Resources yet to fulfilled for a process.
    vector<int> required;
    //Max Need of Resources by a process.
    vector<int> maxNeed;

    //Inputs the process data.
    void getProcessInfo(int n)
    {
        for(int i = 0;i < n;i++)
        {
            int al,m;
            cout<<"Enter the alloted and maximum number of resources for resource "<<(i + 1)<<endl;
            cin>>al>>m;
            if(al > resources.at(i))
            {
                cout<<"Allocation cannot be more than the available resources"<<endl;
            }
            else
            {
                alloted.push_back(al);
                available.at(i) -= al; 
                maxNeed.push_back(m);
                required.push_back(m-al);
            }
        }
    }
};

//Displaying the safe sequence.
void displaySafeSeq(vector<int> v)
{
   for(int i = 0;i < v.size();i++)
   {
       cout<<"P"<<v.at(i)<<" "<<endl;
   }
}

//Linear Search for a vector.
bool search(vector<int> v,int searchEle)
{
    for(int i = 0;i < v.size();i++)
    {
       if(v.at(i) == searchEle)
       {
           return true;
       }
    }
    return false;
}

int main()
{
    //Entering the resource details.
    int n;
    cout<<"Enter the number of resources : ";
    cin>>n;
    for(int i = 0; i < n;i++)
    {
        int rn;
        cin>>rn;
        resources.push_back(rn);
        available.push_back(rn);
    }

    //Getting the process data.
    int pn;
    cout<<"Enter the number of processes :";
    cin>>pn;
    Process p[pn];

    for(int i = 0;i < pn;i++)
    {
       p[i].getProcessInfo(n);
    }

    //Banker's Algorithm
    
    int flag = false;

    for(;safeSequence.size() != pn;)
    {
        int ep = safeSequence.size();
        for(int i = 0;i < pn;i++)
        {
            if(!search(safeSequence,i+1))
            {
                for(int j = 0;j < n;j++)  
                {
                    if(p[i].required.at(j) <= available.at(j))
                    {
                        flag = true;
                    }
                    else
                    {
                        flag = false;
                        break;
                    }
       }

       if(flag)
       {
         
            safeSequence.push_back((i+1));
            for(int j = 0;j < n;j++)
            {
                available.at(j) += p[i].alloted.at(j);
            }
       }
            }
    }

    if(ep == safeSequence.size())
    {
        cout<<"System in unsafe state. Deadlock has occurred!"<<endl;
        break;
    }
    }
    
    if(safeSequence.size() == pn)
    {
        cout<<"System is in safe state and the safe sequence is : "<<endl;
        displaySafeSeq(safeSequence);
    }
    
    return 0;
}