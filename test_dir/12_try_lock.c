#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

// chef = thread
// stove = val
pthread_mutex_t mutexs_stove[4];
int gas[4] = {100, 100, 100, 100};

void	*routine(void *data)
{
	int *idx = (int *) data;
	for (int i = 0; i < 4; i++)
	{
		if (pthread_mutex_trylock(&mutexs_stove[i]) == 0)
		{
			int use = (rand() % 30) + 1;
			if (gas[i] - use < 0)
			{
				printf ("No more gas in stove[%d], chef_%.2d go home\n", i, *idx);
			}
			else
			{
				gas[i] -= use;
				usleep(500000);
				printf("chef_%.2d, stove[%d], use: %2d, rest: %2d\n", *idx, i, use, gas[i]);
			}
			pthread_mutex_unlock(&mutexs_stove[i]);
			break ;
		}
		else
		{
			if (i == 3)
			{
				printf ("chef_%.2d No stove available wait... \n", *idx);
				usleep(300000);
				i = 0;
			}
		}
	}
	free (data);
	return (NULL);
}

int main(void)
{
	pthread_t	th[10];
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		pthread_mutex_init (&mutexs_stove[i], NULL);
	}
	for (int i = 0; i < 10; i++)
	{
		int *idx = malloc(sizeof(int));
		*idx = i;
		if (pthread_create(&th[i], NULL, &routine, idx))
		{
			perror ("Faild on create thread");
			return (1);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (pthread_join(th[i], NULL))
		{
			perror ("Faild on join thread");
			return (2);
		}
	}
	for (int i = 0; i < 4; i++)
	{
		pthread_mutex_destroy (&mutexs_stove[i]);
	}
}