#include <stdio.h>
#define N 5
#define M 4 

int available[M] = {1, 5, 2, 0};
int sequence[N], s=0;

int max[N][M] = {{0, 0, 1, 2},
                 {1, 7, 5, 0},
                 {2, 3, 5, 6},
                 {0, 6, 5, 2},
                 {0, 6, 5, 6}};

int allocation[N][M] = {{0, 0, 1, 2},
                        {1, 0, 0, 0},
                        {1, 3, 5, 4},
                        {0, 6, 3, 2},
                        {0, 0, 1, 4}};

int need[N][M];

void printNeed()
{
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<M; j++)
            printf("%d ", need[i][j]);
        printf("\n");
    }
}

void safetyCheck()
{
    int work[M];
    int finish[N] = {};

    for(int i=0; i<M; i++)
        work[i]=available[i];    

    for(int j=0; j<M; j++)
        for(int i=0; i<N; i++)
            if(finish[i]==0)
            {
                int flag=1;
                for(int k=0; k<M; k++)
                    if(need[i][k]>work[k])
                    {
                        flag=0;
                        break;
                    }
                
                if(flag)
                {
                    for(int x=0; x<M; x++)
                        work[x]+=allocation[i][x];
                    finish[i]=1;
                    sequence[s++]=i;
                }
            }


    int safety=1;
    for(int i=0; i<N; i++)
        if(finish[i]==0)
        {
            safety=0;
            break;
        }
    
    if(safety)
    {
        printf("SAFE\nSequence: ");
        for(int i=0; i<N; i++)
            printf("%d ", sequence[i]);
    }
    else
        printf("NOT SAFE\n");
}

int main()
{
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            need[i][j] = max[i][j]-allocation[i][j];

    printNeed();
    printf("\n");

    safetyCheck();
}