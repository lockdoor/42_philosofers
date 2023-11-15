#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define TN 10

pthread_mutex_t mutex_fuel = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_water = PTHREAD_MUTEX_INITIALIZER;
int fuel = 0;
int water = 0;

void *routine(void *arg)
{
	(void) arg;
	printf ("thread_%d begin\n", *(int *)arg);
	if (rand() % 2 == 0)
	{
		pthread_mutex_lock(&mutex_fuel);
		printf ("thread_%d lock_fuel\n", *(int *)arg);
		// sleep(1);
		pthread_mutex_lock(&mutex_water);
		printf ("thread_%d lock_water\n", *(int *)arg);
	}
	else{
		pthread_mutex_lock(&mutex_water);
		printf ("thread_%d lock_water\n", *(int *)arg);
		// sleep(1);
		pthread_mutex_lock(&mutex_fuel);
		printf ("thread_%d lock_fuel\n", *(int *)arg);
	}

	fuel += 50;
	water = fuel + 10;
	pthread_mutex_unlock(&mutex_fuel);
	printf ("thread_%d unlock_fuel\n", *(int *)arg);
	pthread_mutex_unlock(&mutex_water);
	printf ("thread_%d unlock_water\n", *(int *)arg);
	printf ("thread_%d finished\n", *(int *)arg);
	return (NULL);
}

int main(void)
{
	srand(time(NULL));
	pthread_t th[TN];
	int n[TN] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	for (int i = 0; i < TN; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, &n[i]))
		{
			perror ("Failed on create thread");
		}
	}
	for (int i = 0; i < TN; i++)
	{
		if (pthread_join(th[i], NULL))
		{
			perror ("Failed on join thread");
		}
	}
	printf("fuel: %d, water: %d\n", fuel, water);
	return (0);
}