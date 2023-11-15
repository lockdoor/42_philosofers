#include <stdio.h>
#include <pthread.h>

#define SIZE 16

pthread_mutex_t mutex;

void *routine(void *data)
{
	int *mails = (int *) data;
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		*mails += 1;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main(void)
{
	pthread_t t[SIZE];
	int mails = 0;
	pthread_mutex_init(&mutex, NULL);
	for (int i = 0; i < SIZE; i++)
	{
		if (pthread_create(&t[i], NULL, routine, &mails))
		{
			perror ("Failed to create thread");
			return (i + 1);
		}
		printf ("Thread %d has started\n", i);
	}
	for (int i = 0; i < SIZE; i++)
	{
		if (pthread_join(t[i], NULL))
		{
			perror ("Failed to join thread");
			return (i + SIZE + 1);
		}
		printf ("Thread %d has finished\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("mails: %d\n", mails);
	return (0);
}
