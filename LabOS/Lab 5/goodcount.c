#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>

#define NITER 1000000
sem_t semaphore;
int cnt = 0;

void * Count(void * a)
{
    int i, tmp;
    for(i = 0; i < NITER; i++)
    {
    	sem_wait(&semaphore);//Checking if the resource is available, if not, locking
        tmp = cnt;      /* copy the global cnt locally */
        tmp = tmp+1;    /* increment the local copy */
        cnt = tmp;      /* store the local value into the global cnt */ 
        sem_post(&semaphore);//Freeing the resource
    }
}

int main(int argc, char * argv[])
{
    pthread_t tid1, tid2;
    sem_init(&semaphore, 0, 1);//Starting the semaphore, without sharing between forks and with only one 
							   //position available in the critical section
    if(pthread_create(&tid1, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 1");
      exit(1);
    }

    if(pthread_create(&tid2, NULL, Count, NULL))
    {
      printf("\n ERROR creating thread 2");
      exit(1);
    }

    if(pthread_join(tid1, NULL))	/* wait for the thread 1 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }

    if(pthread_join(tid2, NULL))        /* wait for the thread 2 to finish */
    {
      printf("\n ERROR joining thread");
      exit(1);
    }
    sem_destroy(&semaphore); 

    if (cnt < 2 * NITER) 
        printf("\n BOOM! the count is [%d], should be %d\n", cnt, 2*NITER);
    else
        printf("\n OK! the count is [%d]\n", cnt);
  
    pthread_exit(NULL);
}