#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *routine(void *arg)
{
	(void) arg;
	sleep(9);
	printf ("I am thread\n");
	return (NULL);
}

int main(void)
{
	pthread_t p;
	pthread_create(&p, NULL, &routine,NULL);
	pthread_join(p, NULL);
	printf ("I am parent\n");
	return(0);
}