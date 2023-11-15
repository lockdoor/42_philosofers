#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t	mutex_fuel;
pthread_cond_t	cond_fuel;
int		fuel = 0;

void	*fill_fuel()
{
	for (int i = 0; i < 5; i++)
	{
		pthread_mutex_lock(&mutex_fuel);
		fuel += 15;
		printf ("fuel in tank: %d\n", fuel);
		pthread_mutex_unlock(&mutex_fuel);
		pthread_cond_signal(&cond_fuel);
		sleep(1);
	}
	return (NULL);
}

void	*drive()
{
	pthread_mutex_lock(&mutex_fuel);
	while (fuel <= 40)
	{
		printf("wait for fuel\n");
		// sleep(1);
		pthread_cond_wait(&cond_fuel, &mutex_fuel);
	}
	fuel -= 40;
	printf("drive: %d\n", fuel);
	// sleep(1);
	pthread_mutex_unlock(&mutex_fuel);
	return (NULL);
}

int	main(void)
{
	pthread_t th[2];
	pthread_mutex_init(&mutex_fuel, NULL);
	pthread_cond_init(&cond_fuel, NULL);
	for (int i = 0; i < 2; i++)
	{
		if (i == 0){
			if (pthread_create(&th[i], NULL, &drive, NULL))
			{
				perror("Faild create thread");
				return (1);
			}
		}
		else
		{
			if (pthread_create(&th[i], NULL, &fill_fuel, NULL))
			{
				perror("Faild create thread");
				return (1);
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		if (pthread_join(th[i], NULL))
		{
			perror("Faild join thread");
			return (1);
		}
	}
	pthread_mutex_destroy(&mutex_fuel);
	pthread_cond_destroy(&cond_fuel);
	return (0);
}