#include<bits/stdc++.h>
using namespace std;

struct process
{
int arrival,burst,priority,pNo;
};

process P[5][10];
void RoundRobin(int n, int quantum)
{
    int RembTime[]={15,20,20,20,5,15};
    int waiting[6],turnAround[6];
    int sumBurst=0;
    int Q = quantum;
    float avgW=0,avgTat=0;
    queue<int> serial;
    int time=0, remQuantum=0;
    while(1)
    {
        bool done = true;
        for(int i=0;i<n;i++)
        {
            if(time>=P[2][i].arrival)
            {
            if(RembTime[i]>0)
            {
                serial.push(P[2][i].pNo);
                done = false;


                if(RembTime[i]>Q)
                {
                    time+=Q;
                    RembTime[i]-=Q;
                    Q= quantum;
                }
                else
                {
                    time+=RembTime[i];
                    waiting[i]=time-P[2][i].burst;
                    Q= quantum + (Q - RembTime[i]);
                    RembTime[i]=0;
                }
            }
            }
            else
            {
                break;
            }
        }
        if(done==true)
            break;
    }


    for(int i=0;i<n;i++)
    {
        turnAround[i] = waiting[i]+P[2][i].burst;
    }
    cout<<"Round Robin Scheduling"<<endl;
    cout<<"Scheduling Order: ";
    while(!serial.empty())
    {
        cout<<"P"<<serial.front()<<" ";
        serial.pop();
    }
    cout<<endl<<"Process     Waiting Time   TurnAround Time"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<"P"<<P[2][i].pNo<<"\t\t"<<waiting[i]<<"\t\t"<<turnAround[i]<<endl;
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

    RoundRobin(n,10);

    return 0;
}
