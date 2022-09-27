#include <stdio.h>
#include <pthread.h>

int thread_num = 20;

int turn;
const int MAX = 100;
int ans = 0;

int flag[20];

void lock_init()
{
	int i;
	for(i=0;i<thread_num;i++)
	{
		flag[i] = 0;
	}
	turn = 0;
}

//critical section
void lock(int x)
{
	if(x <= thread_num-1 && x >=0)
	{
		flag[thread_num] = 1;
	}

    turn = thread_num-x;

	if(thread_num-2-x >= 0)
	{
		while (flag[thread_num-2-x]==1 && turn==thread_num-x) ;
	}
	else if(thread_num-1-x != x)
	{
		while (flag[thread_num-1-x]==1 && turn==thread_num-x) ;
	}
}

//not critical section
void unlock(int y)
{
	if(y <= thread_num && y >= 0)
	{
		flag[y] = 0;
	}
}

void* func(void *arg)
{
	int i = 0;
	int z = (int)arg;

	lock(z);

	//critical section starts here
	printf("Thread Entered: %d\n", z);

	for (i=0; i<MAX; i++)
		ans++;

	//critical section ends here
	unlock(z);
}

int main()
{
	pthread_t threads[thread_num];
	lock_init();

	void *value[thread_num];

	int count;
	for (count = 0; count < thread_num; ++count)
	{
		if (pthread_create(&threads[count], NULL,func,(void*)count) != 0)
		{
		  printf("Cannot create thread # %d\n", count);
		  break;
		}
	}

	for (int i = 0; i < thread_num; ++i)
	{
		if (pthread_join(threads[i], &value[i]) != 0)
		{
		  printf("Cannot join thread # %d\n", i);
		}
	}

	printf("Ans variable after each thread: %d | Ans should be : %d\n", ans, MAX*thread_num);

	return 0;
}
