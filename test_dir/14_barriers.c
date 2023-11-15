#include <pthread.h>
#include <stdio.h>
#define TH 10

// no behavier available in mac_os
pthread_barrier_t barrier;

void	*routine(void *arg)
{
	(void) arg;
	printf ("wait for barrier\n");
	pthread_barrier_wait(&barrier);
	printf ("finish\n");
	return (NULL);
}

int	main(void)
{
	pthread_t th[TH];
	pthread_barrier_init(&barrier, NULL, TH);
	for (int i = 0; i < TH; i++)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL))
		{
			perror ("Failed on create thread");
			return (1);
		}
	}
	for (int i = 0; i < TH; i++)
	{
		if (pthread_join(th[i], NULL))
		{
			perror ("Failed on join thread");
			return (2);
		}
	}
	pthread_barrier_destroy(&barrier);
	return (0);
}
