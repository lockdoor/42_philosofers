#include <stdio.h>
#include <pthread.h>

/* race condition */
void *routine(void *data)
{
	int *mails = (int *) data;
	for (int i = 0; i < 100; i++)
	{
		*mails += 1;
	}
	return (NULL);
}

int main(void)
{
	pthread_t t1, t2;
	int mails = 0;
	if (pthread_create(&t1, NULL, routine, &mails))
		return (1);
	if (pthread_create(&t2, NULL, routine, &mails))
		return (2);
	if (pthread_join(t1, NULL))
		return (3);
	if (pthread_join(t2, NULL))
		return (4);
	printf("mails: %d\n", mails);
	return (0);
}
