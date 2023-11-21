#include <semaphore.h>
#include <stdio.h>


int main(void)
{
	sem_t	*sem_1;
	sem_t	*sem_2;

	sem_1 = sem_open("my_sem", O_CREAT | O_EXCL, 0644, 0);
	if (sem_1 == SEM_FAILED)
	{
		perror ("sem_1");
		return (1);
	}
	sem_2 = sem_open("my_sem", O_CREAT | O_EXCL, 0644, 0);
	if (sem_2 == SEM_FAILED)
	{
		sem_close(sem_1);
		perror ("sem_2");
		return (1);
	}
	sem_close(sem_1);
	sem_close(sem_2);
	return (0);
}