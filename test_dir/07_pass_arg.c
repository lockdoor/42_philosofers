#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int	prime[SIZE] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
	int *idx = (int *) arg;
	printf("%d, ", prime[*idx]);
	free (idx);
	return (NULL);
}

int main(void)
{
	pthread_t th[SIZE];
	for (int i = 0; i < SIZE; i++)
	{
		int *idx = malloc(sizeof(int));
		*idx = i;
		if (pthread_create(&th[i], NULL, &routine, idx))
		{
			perror("Error on create thread");
			return (1);
		}
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (pthread_join(th[i], NULL))
		{
			perror("Error on join thread");
			return (2);
		}
	}
	return (0);
}