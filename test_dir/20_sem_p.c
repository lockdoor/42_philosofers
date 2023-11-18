#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
    sem_t   *sem;
    int     pn;
    char    *s = "555";
    int     *nb = (int *)malloc(sizeof(int));
    *nb = 10;

    pn = 6;
    sem = sem_open("my_sem", O_CREAT | O_EXCL, 0644, 1);
    sem_unlink("my_sem");

    pid_t   id[pn];
    for (int i = 0; i < pn; i++)
    {
        id[i] = fork();
        if (id[i] == 0)
        {
            for (int j = 0; j < 2; j++)
            {
                sem_wait(sem);
                sleep (1);
                *nb += 10;
                printf("I am child, %s, %p, %d, %p\n", s, s, *nb, nb);
                sleep (1);

                sem_post(sem);
            }
            return (0);
        }
    }
    sem_close(sem);
    for (int i = 0; i < pn; i++)
    {
        waitpid(id[i], NULL, 0);
    }

    return (0);
}