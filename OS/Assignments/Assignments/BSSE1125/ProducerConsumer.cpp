#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <random>
#include <sys/types.h>

using namespace std;

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in,out;

int x, counter=0, count;

bool flag[2];

void* produce(void* arg){
	while(1){
		sleep(1);

		x=0;
		flag[1]=true;

		while(flag[0]&&x==0);

		int item = rand()%100;
		buffer[in] = item;
		cout<<"Produced "<<item<<endl;
		in = (in + 1) % BUFFER SIZE;
        count++;

        flag[1]=false;
	}
}

void* consume(void* arg){
	while(1){
		sleep(1);

		flag[0]=true;
		x=1;

		while(flag[1]&&x==1);

		int item = buffer[out];
		cout<<"Consumed "<<item<<endl;
		out = (out + 1) % BUFFER_SIZE;
		count--;

		flag[0]=false;
	}
}

int main(){
	pthread_t producer,consumer;
	pthread_attr_t attr1,attr2;
	pthread_attr_init(&attr1);
	pthread_attr_init(&attr2);

	pthread_create(&producer,NULL,produce,NULL);
	pthread_create(&consumer,NULL,consume,NULL);
	pthread_exit(NULL);
}
