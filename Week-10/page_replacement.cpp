#include<iostream>
#include<vector>
#include<algorithm>
#include <limits.h>
using namespace std;

// Linear Search in a vector of integers.
int find(vector<int> x,int searchElement)
{
    for(int i = 0;i < x.size();i++)
    {
        if(x[i] == searchElement)
        {
            return i;
        }
    }

    return -1;
}

// Class with all page replacement algorithms.
class PageReplacementAlgorithms
{
    public:
      vector<int> reference_string;
      int n, hit, miss;

      PageReplacementAlgorithms(){}

      // Data Entry.
      void getData(int n,int rlength)
      {
          this->n = n;
          this->hit = 0;
          this->miss = 0;
          getReferenceString(rlength);
      }
      
      // First In First Out Algorithm 
      void FIFO()
      {
          vector<int> stack;
          vector<int> entry;         
          
          cout<<"Length : "<<reference_string.size()<<endl;

          for(int i = 0;i < reference_string.size();i++)
          {
            // A hit.
            if(find(stack,reference_string[i]) != -1)
            {
                hit++;
            }
            else
            {
             // if there is a miss
             miss++;
             if(stack.size() < n)
             {
                stack.push_back(reference_string[i]);
                entry.push_back(i);
             }
             else
             {
                vector<int>::iterator minElement = min_element(entry.begin(),entry.end());
                int minIndex = distance(entry.begin(),minElement);

                stack[minIndex] = reference_string[i];
             }
            }
          }

           hit -= n;
           miss += n;
      }

      // Optimal Page Replacement Algorithm.
      void optimal()
      {
          vector<int> stack;       

          for(int i = 0;i < reference_string.size();i++)
          {
            // A hit.
            int index = find(stack,reference_string[i]);
            if(index != -1)
            {
                hit++;
            }
            else
            {
             // if there is a miss
             miss++;
             if(stack.size() < n)
             {
                stack.push_back(reference_string[i]);
             }
             else
             {
                int replaceIndex = getReplaceIndex(stack,i); 
                stack[replaceIndex] = reference_string[i];
             }
            }
          }
      }

      // Least Recently used Algorithm.
      void LRU()
      {
          vector<int> stack;
          vector<int> recency;         

          for(int i = 0;i < reference_string.size();i++)
          {
            // A hit.
            int index = find(stack,reference_string[i]);
            if(index != -1)
            {
                hit++;
                recency[index] = i;
            }
            else
            {
             // if there is a miss
             miss++;
             if(stack.size() < n)
             {
                stack.push_back(reference_string[i]);
                recency.push_back(i);
             }
             else
             {
                vector<int>::iterator minElement = min_element(recency.begin(),recency.end());
                int minIndex = distance(recency.begin(),minElement);

                stack[minIndex] = reference_string[i];
                recency[minIndex] = i;
             }
            }
          }
      }

      // Resetting the parameters.
      void resetParams()
      {
          this->hit = 0;
          this->miss = 0;
      }

      // Displaying all the parameters.
      void displayParams()
      {
          cout<<"No.of hits = "<<hit<<endl;
          cout<<"No.of miss = "<<miss<<endl;
      }

      private:
       // Computation of the replacement index.
       int getReplaceIndex(vector<int> x,int offset)
       {
           vector<int> counts;
           for(int i = 0;i < x.size();i++)
           {
               int d = INT_MAX;
               for(int j = offset;j < reference_string.size();j++)
               {
                   if(reference_string[j] == x[i])
                   {
                       d = j - offset;
                       break;
                   }
               }
               counts.push_back(d);
           }

           vector<int>::iterator minElement = max_element(counts.begin(),counts.end());
           int minIndex = distance(counts.begin(),minElement);

           return minIndex;
       }

       // Reference String Input function.
       void getReferenceString(int rlength)
       {
         cout<<"Input the reference string : "<<endl;
         for(int i = 0;i < rlength;i++)
         {
             int temp = 0;
             
             cin>>temp;

             reference_string.push_back(temp);
         }
       }
};

// Displaying the menu.
void displayMenu()
{
    cout<<"Menu"<<endl;
    cout<<"1. Data Entry"<<endl;
    cout<<"2. FIFO"<<endl;
    cout<<"3. Optimal"<<endl;
    cout<<"4. LRU"<<endl;
    cout<<"5. Exit"<<endl;
}

int main()
{
    PageReplacementAlgorithms p;

    int choice = 1,rlength,frames;

    while(choice < 5)
    {
       displayMenu();

       cin>>choice;

       switch(choice)
       {
           case 1:
             cout<<"Enter the number of frames : ";
             cin>>frames;
             cout<<endl<<"Enter the number of references : ";
             cin>>rlength;
             p.getData(frames,rlength);
             break;
           case 2:
             p.FIFO();
             p.displayParams();
             p.resetParams();
             break;
           case 3:
             p.optimal();
             p.displayParams();
             p.resetParams();
             break;
          case 4:
             p.LRU();
             p.displayParams();
             p.resetParams();
             break;
          case 5:
             cout<<"Exiting.."<<endl;
             break;
          default:
             cout<<"Invalid Input"<<endl;
       }
    }

    return 0;
}