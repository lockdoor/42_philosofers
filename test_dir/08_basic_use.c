#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int	prime[SIZE] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
	int *idx = (int *) arg;
	int n = SIZE / 2;
	int res = 0;
	for (int i = 0; i < n; i++)
	{
		res += prime[i + (*idx * n)];
	}
	printf("thread %d: %d\n", *idx, res);
	*idx = res;
	return (idx);
}

int main(void)
{
	pthread_t th[2];
	for (int i = 0; i < 2; i++)
	{
		int *idx = malloc(sizeof(int));
		*idx = i;
		if (pthread_create(&th[i], NULL, &routine, idx))
		{
			perror("Error on create thread");
			return (1);
		}
	}
	int global_res = 0;
	for (int i = 0; i < 2; i++)
	{
		int *res;
		if (pthread_join(th[i], (void **)&res))
		{
			perror("Error on join thread");
			return (2);
		}
		global_res += *res;
		free (res);
	}
	printf ("global: %d\n", global_res);
	return (0);
}