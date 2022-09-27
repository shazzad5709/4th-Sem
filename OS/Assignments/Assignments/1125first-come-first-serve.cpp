#include<bits/stdc++.h>
using namespace std;

void findWaitTime(int process[], int n, int bt[],
                  int wt[], int at[])
{
    int st[n];
    st[0] = 0;
    wt[0] = 0;
    cout<<"Waiting Time :"<<"\n\n";

    for (int i=1; i<n ; i++)
    {
        st[i] = st[i-1] + bt[i-1];
        wt[i] = st[i] - at[i];

        if (wt[i] < 0)
            wt[i] = 0;
    }
    for (int i=0; i<n ; i++)
    {
        cout<<process[i]<<"-->\t\t"<<wt[i]<<"\n";
    }
}

void findTaTime(int process[], int n, int bt[],
                int wt[], int tat[])
{
    cout<<"\nTurn Around Time :"<<"\n\n";

    for (int i=0; i<n ; i++)
        tat[i] = bt[i] + wt[i];
    for (int i=0; i<n ; i++)
    {
        cout<<process[i]<<"-->\t\t"<<tat[i]<<"\n";
    }
}

void findavgTime(int process[], int n, int burst[], int at[])
{
    int wtime[n], tatime[n];

    findWaitTime(process, n, burst, wtime, at);
    findTaTime(process, n, burst, wtime, tatime);

    int total_wtime = 0, total_tatime = 0;
    for (int i=0 ; i<n ; i++)
    {
        total_wtime = total_wtime + wtime[i];
        total_tatime = total_tatime + tatime[i];
        int compl_time = tatime[i] + at[i];
    }

    cout << "Average waiting time = "
         << (float)total_wtime / (float)n;
    cout << "\nAverage turn around time = "
         << (float)total_tatime / (float)n;
}

int main()
{
    int n=6;

    int processid[] = {1,2,3,4,5,6};
    int burst_time[] = {15,20,20,20,5,15};
    int arrival_time[] = {0,0,20,25,45,55};
    int priority[] = {8,3,4,4,5,5};

    cout<<"Process executed in this order : ";

    for(int i=0; i<n; i++)
    {
        cout<<processid[i] <<" ";
    }

    cout<<"\n";

    findavgTime(processid, n, burst_time, arrival_time);
    return 0;
}
