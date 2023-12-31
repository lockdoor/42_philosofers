#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define	TH 20

sem_t *sem;

void	*routine(void *arg)
{
	int n = *(int *)arg;
	sem_wait(sem);
	printf("thread: %d\n", n);
	sleep(1);
	sem_post(sem);
	return (arg);
}


int	main(void)
{
	pthread_t	th[TH];
	int			i;

	srand(time(NULL));
	sem = sem_open("my_sem", O_CREAT | O_EXCL, 0644, 2);
	sem_unlink("my_sem");
	i = 0;
	while (i < TH)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a))
		{
			perror ("Failed on create thread");
		}
		i++ ;
	}
	i = 0;
	while (i < TH)
	{
		int	*b;
		if (pthread_join(th[i], (void **)&b))
		{
			perror ("Failed on join thread");
		}
		free (b);
		i++ ;
	}
	sem_close(sem);
	return (0);
}
