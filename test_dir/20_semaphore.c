#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

#define TN 10

sem_t smp;

void *routine(void *arg)
{
	(void) arg;
	sem_wait(&smp);
	sleep (2);
	printf ("thread execute finished\n");
	sem_post(&smp);
	return (NULL);
}

int main(void)
{
	pthread_t th[TN];
	sem_init(&smp, 0, 5);
	for (int i = 0; i < TN; i++)
	{
		if(pthread_create(&th[i], NULL, &routine, NULL))
		{
			perror ("Failed on create thread");
		}
	}
	for (int i = 0; i < TN; i++)
	{
		if(pthread_join(th[i], NULL))
		{
			perror ("Failed on join thread");
		}
	}
	sem_destroy(&smp);
	return (0);
}
