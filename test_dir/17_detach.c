#include <pthread.h>
#include <printf.h>
#include <errno.h>
#include <unistd.h>

#define TN 2

void	*routine(void *arg)
{
	(void)	arg;
	sleep(1);
	printf("finished execute\n");
	return (NULL);
}

int	main(void)
{
	pthread_t th[TN];
	pthread_attr_t detached_thread;
	pthread_attr_init(&detached_thread);
	pthread_attr_setdetachstate(&detached_thread, PTHREAD_CREATE_DETACHED);
	for (int i = 0; i < TN; i++)
	{
		if (pthread_create(&th[i], &detached_thread, &routine, NULL))
		{
			perror ("Faild on create thread");
		}
		// sleep(2);
		// pthread_detach(th[i]);
	}
	// for (int i = 0; i < TN; i++)
	// {
	// 	if (pthread_join(th[i], NULL))
	// 	{
	// 		perror ("Faild on join thread");
	// 	}
	// }
	// return (0);
	pthread_exit(0);
}