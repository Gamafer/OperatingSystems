#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

int g = 0;
sem_t sem;

void *function(void *args)
{
    int *id = (int *)args;

    printf("Thread %d entering critical section\n", *id);

    sem_wait(&sem);

    printf("Thread %d in critical section\n", *id);

    g++; //Wants to modify the 'g' variable

    sleep(3);

    printf("Thread %d outside critical section\n", *id);

    sem_post(&sem);

};

int main()
{

    sem_init(&sem, 0, 1);   //1 = amount of available resources

    pthread_t tid1, tid2;

    int id1 = 1;
    int id2 = 2;

    pthread_create(&tid1, NULL, function, (void *)&id1);
    pthread_create(&tid2, NULL, function, (void *)&id2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    sem_destroy(&sem);

    return 0;
}