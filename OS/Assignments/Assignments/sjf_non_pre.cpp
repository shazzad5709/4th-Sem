#include <iostream>
#include<bits/stdc++.h>

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

void SjfNon(int n)
{
    sort(P[3],P[3]+n,comp);
    int time=0,k=1,min;
    for(int i=0;i<n;i++)
    {
        time+=P[3][i].burst;
        min=P[3][k].burst;
        for(int j=k;j<n;j++)
        {
            if(time>=P[3][j].arrival && P[3][j].burst<min)
            {
                min = P[3][j].burst;
                process temp = P[3][j];
                P[3][j] = P[3][k];
                P[3][k]= temp;
            }
        }
        k++;
    }
    int waiting[6],turnAround[6];
    int sumBurst=0;
    float avgW=0,avgTat=0;
    for(int i=0;i<n;i++)
    {
        waiting[i] = sumBurst-P[3][i].arrival;
        sumBurst+=P[3][i].burst;
        turnAround[i] = waiting[i]+P[3][i].burst;
    }
    cout<<"Shortest Job First(Non Preemptive)"<<endl;
    cout<<"Scheduling Order: ";
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<P[3][i].pNo<<" ";
    }
    cout<<endl<<"Process     Waiting Time   TurnAround Time"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<P[3][i].pNo<<"\t\t"<<waiting[i]<<"\t\t"<<turnAround[i]<<endl;
        avgW+=waiting[i];
        avgTat+=turnAround[i];
    }
    cout<<"Average waiting time: "<<(float)avgW/(float)n<<endl<<"Average TurnAround Time: "<<(float)avgTat/(float)n<<endl<<endl;
}

void SjfPreemp(int n, int* burst)
{
    int minBurst=INT_MAX,smallest=0,count=0,time=0,end;
    int waiting[6],turnAround[6];
    float avgW=0,avgTat=0;
    bool check = false;
    queue<int> serial;
    while(count!=n)
    {
            for(int i = 0; i < n; i++)
            {
                  if(P[4][i].arrival <= time && P[4][i].burst< minBurst && P[4][i].burst > 0)
                  {
                      minBurst = P[4][i].burst;
                      smallest = i;
                      check = true;
                  }
            }
            if(check==false)
            {
                time++;
                continue;
            }

            P[4][smallest].burst--;
            minBurst = P[4][smallest].burst;
            if(minBurst==0)
            {
                minBurst = INT_MAX;
            }
            if(P[4][smallest].burst == 0)
            {
                  serial.push(P[4][smallest].pNo);
                  count++;
                  check = false;
                  end = time + 1;
                  waiting[smallest] = end - burst[smallest]- P[4][smallest].arrival;
                  turnAround[smallest] = waiting[smallest] + burst[smallest];

            }
            time++;
      }
    cout<<"Shortest Job First(Preemptive)"<<endl;
    cout<<"Scheduling Order: ";
    while(!serial.empty())
    {
        cout<<"P"<<serial.front()<<" ";
        serial.pop();
    }
    cout<<endl<<"Process     Waiting Time   TurnAround Time"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<P[4][i].pNo<<"\t\t"<<waiting[i]<<"\t\t"<<turnAround[i]<<endl;
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
    SjfNon(n);
    SjfPreemp(n,burstTime);
    return 0;
}
