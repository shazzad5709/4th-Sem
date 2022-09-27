#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

int main()
{
    __pid_t pid, sid;
    pid = fork();

    if(pid<0)
        exit(EXIT_FAILURE);
    else if(pid>0)
        exit(EXIT_SUCCESS);

    umask(0);

    sid = setsid();
    if(sid<0)
        exit(EXIT_FAILURE);
    
    if((chdir("/"))<0)
        exit(EXIT_FAILURE);
    
    while(1)
    {
        sleep(10);
        printf("tic\n");
    }
}