#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define	TH 20
#define	NB 10

int	n[NB];
int idx = 0;
sem_t *full;
sem_t *empty;
pthread_mutex_t mutex;
int count = 0;

// void *producer(void *arg)
// {
// 	(void) arg;
// 	while (1)
// 	{
// 		// usleep (1);
// 		sem_wait(empty);
// 		// printf("count: %d\n", count++);
// 		pthread_mutex_lock(&mutex);
// 		count++;
// 		pthread_mutex_unlock(&mutex);
// 		sem_post(full);
// 	}
// 	return (NULL);
// }

// void *consumer(void *arg)
// {
// 	(void) arg;
// 	while (1)
// 	{
// 		sem_wait(full);
// 		pthread_mutex_lock(&mutex);
// 		printf("count: %d\n", --count);
// 		pthread_mutex_unlock(&mutex);
// 		sem_post(empty);
// 	}
// 	return (NULL);
// }

void	*producer(void *arg)
{
	(void) arg;
	while (1)
	{
		int x = rand() % 100;
		sleep (1);
		sem_wait(empty);
		pthread_mutex_lock(&mutex);
		n[idx] = x;
		idx++ ;
		pthread_mutex_unlock(&mutex);
		sem_post(full);
	}
	return (NULL);
}

void	*consumer(void *arg)
{
	int	t = *(int *)arg;
	while (1)
	{
		int y;
		int i;
		// sleep(1);
		sem_wait(full);
		pthread_mutex_lock(&mutex);
		i = --idx;
		y = n[i];
		pthread_mutex_unlock(&mutex);
		sem_post(empty);

		printf("t: %d, n: %d, i: %d\n", t, y, i);
	}
	free (arg);
	return (NULL);
}

int	main(void)
{
	pthread_t	th[TH];

	srand(time(NULL));
	pthread_mutex_init(&mutex, NULL);
	empty = sem_open("empty", O_CREAT | O_EXCL, 0644, NB);
	full = sem_open("full", O_CREAT | O_EXCL, 0644, 0);
	sem_unlink("empty");
	sem_unlink("full");

	for (int i = 0; i < TH; i++)
	{
		if (i > 14)
		{
			if (pthread_create(&th[i], NULL, &producer, NULL))
			{
				perror("Faild create producer");
			}

		}
		else
		{
			int *a = malloc(sizeof(int));
			*a = i + 1;
			if (pthread_create(&th[i], NULL, &consumer, a))
			{
				perror("Faild create comsumer");
			}
		}
	}
	for (int i = 0; i < TH; i++)
	{
		if (pthread_join(th[i], NULL))
		{
			perror("Faild join thread");
		}
		// if (pthread_join(th[i], NULL))
		// {
		// 	perror("Faild join consumer");
		// }
	}

	pthread_mutex_destroy(&mutex);
	sem_close(empty);
	sem_close(full);
	return (0);
}