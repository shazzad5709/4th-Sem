#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define N 10
int readCount, writeCount, count=5, pc=0;
sem_t readMutex, writeMutex, readTry, resource;
pthread_t read_t[10], write_t[10];

void *reader(void *rn)
{
    sem_wait(&readTry);
    sem_wait(&readMutex);
    readCount++;

    if(readCount==1)
        sem_wait(&resource);

    sem_post(&readMutex);
    sem_post(&readTry);

    printf("Reader: %d\t Value: %d\n", *(int*)rn, count);
    //pc++;

    sem_wait(&readMutex);
    readCount--;

    if(readCount==0)
        sem_post(&resource);
    
    sem_post(&readMutex);
}

void *writer(void *wn)
{
    sem_wait(&writeMutex);
    writeCount++;

    if(writeCount==1)
        sem_wait(&readTry);
    
    sem_post(&writeMutex);
    sem_post(&resource);

    count *= 2;
    printf("Writer: %d\t Updated Value: %d\n", *(int*)wn, count);
    //pc++;
    sem_post(&resource);

    sem_wait(&writeMutex);
    writeCount--;

    if(writeCount==0)
        sem_post(&readTry);

    sem_post(&writeMutex);
}

int main()
{
    sem_init(&readMutex, 0, 1);
    sem_init(&writeMutex, 0, 1);
    sem_init(&readTry, 0, 1);
    sem_init(&resource, 0, 1);

    for(int i=0; i<N; i++)
    {
        int *a=(int*)malloc(sizeof(int));
        *a=i+1;
        pthread_create(&read_t[i-1], NULL, (void*)reader, a);
        pthread_create(&write_t[i-1], NULL, (void*)writer, a);
    }

    for(int i=0; i<N; i++)
    {
        pthread_join(read_t[i], NULL);
        pthread_join(write_t[i], NULL);
    }
    //printf("Count: %d\n", pc);
}