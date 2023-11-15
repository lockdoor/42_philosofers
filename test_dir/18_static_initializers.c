#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

pthread_mutex_t	mutex_fuel = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t	cond_fuel = PTHREAD_COND_INITIALIZER;
int		fuel = 0;

void	*fill_fuel()
{
	for (int i = 0; i < 4; i++)
	{
		pthread_mutex_lock(&mutex_fuel);
		fuel += 40;
		printf ("fuel in tank: %d\n", fuel);
		pthread_mutex_unlock(&mutex_fuel);
		// pthread_cond_signal(&cond_fuel);
		pthread_cond_broadcast(&cond_fuel);
		sleep(1);
	}
	return (NULL);
}

void	*drive(void *arg)
{
	pthread_mutex_lock(&mutex_fuel);
	while (fuel < 40)
	{
		printf("car_%.2d: wait for fuel\n", *(int *)arg);
		// sleep(1);
		pthread_cond_wait(&cond_fuel, &mutex_fuel);
	}
	fuel -= 40;
	printf("car_%.2d: drive: %d\n", *(int *)arg,  fuel);
	// sleep(1);
	pthread_mutex_unlock(&mutex_fuel);
    free (arg);
	return (NULL);
}

int	main(void)
{
	pthread_t th[5];
    pthread_attr_t detached_thread;
	pthread_attr_init(&detached_thread);
	pthread_attr_setdetachstate(&detached_thread, PTHREAD_CREATE_DETACHED);
	for (int i = 0; i < 5; i++)
	{
		if (i == 4){
			if (pthread_create(&th[i], &detached_thread, &fill_fuel, NULL))
			{
				perror("Faild create thread");
				return (1);
			}
		}
		else
		{
            int *car = malloc(sizeof(int));
            *car = i + 1;
			if (pthread_create(&th[i], NULL, &drive, car))
			{
				perror("Faild create thread");
				return (1);
			}
		}
	}
	pthread_attr_destroy(&detached_thread);
    pthread_exit(0);
}