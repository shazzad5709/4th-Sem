#include <bits/stdc++.h>

using namespace std;

struct process
{
int arrival,burst,priority,pNo;
};

process P[5][10];

bool comp(process a, process b)
{
    if(a.arrival==b.arrival)
    {
        if(a.priority==b.priority)
        {
            return a.burst<b.burst;
        }
        else
        {
            return a.priority>b.priority;
        }
    }
    else
    {
        return a.arrival<b.arrival;
    }
}

void Priority(int n)
{
    sort(P[1],P[1]+n,comp);
    int waiting[6],turnAround[6];
    int sumBurst=0;
    float avgW=0,avgTat=0;
    for(int i=0;i<n;i++)
    {
        waiting[i] = sumBurst-P[1][i].arrival;
        sumBurst+=P[1][i].burst;
        turnAround[i] = waiting[i]+P[1][i].burst;
    }
    cout<<"Priority Scheduling"<<endl;
    cout<<"Scheduling Order: ";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<P[1][i].pNo<<" ";
    }
    cout<<endl<<"Process     Waiting Time   TurnAround Time"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<P[1][i].pNo<<"\t\t"<<waiting[i]<<"\t\t"<<turnAround[i]<<endl;
        avgW+=waiting[i];
        avgTat+=turnAround[i];
    }
    cout<<"Average waiting time: "<<(float)avgW/(float)n<<endl<<"Average TurnAround Time: "<<(float)avgTat/(float)n<<endl<<endl;

}

int main()
{
    int burstTime[]={15,20,20,20,5,15};
    int arrival[]={0,0,20,25,45,55};
    int priority[]={8,3,4,4,5,5};
    int n=6;
    for(int j=0;j<5;j++)
    {
    for(int i=0;i<n;i++)
    {
    P[j][i].arrival=arrival[i];
    P[j][i].burst=burstTime[i];
    P[j][i].priority=priority[i];
    P[j][i].pNo=i+1;
    }
    }
    Priority(n);   //second process

    return 0;
}
