#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void	*role_dice()
{
	int *res = malloc(sizeof(int));
	*res = (rand() % 6) + 1;
	printf ("[thread]-> res: %d, %p\n", *res, res);
	return (res);
}

int	main(void)
{
	pthread_t th;
	int	*res;
	srand(time(NULL));
	if (pthread_create(&th, NULL, &role_dice, NULL))
	{
		perror ("Error on create thread");
		return (1);
	}
	if (pthread_join(th, (void **)&res))
	{
		perror ("Error on join thread");
		return (2);
	}
	printf ("[main] -> res: %d, %p\n", *res, res);
	free (res);
	return (0);
}
