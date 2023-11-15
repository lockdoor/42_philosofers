#include <stdio.h>
#include <pthread.h>

pthread_mutex_t mutex;

void *routine(void *data)
{
	int *mails = (int *) data;
	for (int i = 0; i < 100000; i++)
	{
		pthread_mutex_lock(&mutex);
		*mails += 1;
		pthread_mutex_unlock(&mutex);
	}
	return (NULL);
}

int main(void)
{
	pthread_t t1, t2;
	int mails = 0;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&t1, NULL, routine, &mails))
		return (1);
	if (pthread_create(&t2, NULL, routine, &mails))
		return (2);
	if (pthread_join(t1, NULL))
		return (3);
	if (pthread_join(t2, NULL))
		return (4);
	pthread_mutex_destroy(&mutex);
	printf("mails: %d\n", mails);
	return (0);
}
