#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#define QUEUE_SIZE   5		/* total number of slots */
#define NP          3		/* total number of producers */
#define NC          3		/* total number of consumers */
#define NITERS      4		/* number of items produced/consumed */

typedef struct {
    int q[QUEUE_SIZE];   /* shared var */
    int front;         	  /* mantains the position of the front element of the queue */
    int count;        	  /* Counts how many elements are in the queue*/
    sem_t full;     	  /* keep track of the number of full spots */
    sem_t empty;    	  /* keep track of the number of empty spots */
    sem_t mutex;    	  /* enforce mutual exclusion to shared data */
} squeue_t;

squeue_t queue;

void queueAdd(int element)
{
  int index;
  /*
   * Calculate index at which to put
   * next element.
   */
  index = (queue.front + queue.count)% QUEUE_SIZE;
  queue.q[index] = element;
  queue.count++;
}

int queueRemove()//Removes the element from the from of the queue and returns it
{
  int element;
  /* Save the element so we can return it. */
  element = queue.q[queue.front];
  /*
   * Advance the index of the front,
   * making sure it wraps around the
   * array properly.
   */
  queue.front++;
  queue.front %= QUEUE_SIZE;
  queue.count--;
  return element;
}


void *Producer(void *arg)
{
    int i, item, index;

    index = (int)arg;

    //printf("Accesses producer\n");

    for (i=0; i < NITERS; i++) {


        /* Produce item */
        item = i;	

        /* Prepare to write item to buf */

        /* If there are no empty slots, wait */
        sem_wait(&queue.empty);
        /* If another thread uses the buffer, wait */
        sem_wait(&queue.mutex);
        queueAdd(item);
        printf("[P%d] Producing %d ...\n", index, item); fflush(stdout);
        //printf("Accesses for within the producer\n");
        /* Release the buffer */
        sem_post(&queue.mutex);
        /* Increment the number of full slots */
        sem_post(&queue.full);

        /* Interleave  producer and consumer execution */
        if (i % 2 == 1) sleep(1);
    }
    return NULL;
}

void *Consumer(void *arg)
{
    int i, item, index;
    index = (int) arg;

    for (i = 0; i < NITERS; i++)
    {
        sem_wait(&queue.full);
        sem_wait(&queue.mutex);

        item = queueRemove();
        printf("[P%d] Consuming %d ...\n", index, item);
        fflush(stdout);

        sem_post(&queue.mutex);
        sem_post(&queue.empty);

        if(i%2 == 1)
            sleep(1);
    }
    
}

int main()
{
    pthread_t idP[NP];
    pthread_t idC[NC];

    int index;
    sem_init(&queue.full, 0, 0);
    sem_init(&queue.empty, 0, QUEUE_SIZE);
    sem_init(&queue.mutex, 0, 1);
    //Add the code to initialize the empty and the mutual exclusion semaphores
   
   //printf("Accesses the main\n");

    for (index = 0; index < NP; index++)
    {  
        //printf("\nAccesses the for\n");
       /* Create a new producer */
       pthread_create(&idP[index], NULL, Producer, (void*)index);
    }

   for (index = 0; index < NC; index++)
   {
       /* New consumer */
       pthread_create(&idC[index], NULL, Consumer, (void*)index);
   }
   
   for (index = 0; index < NP; index++)
   {
       /* code */
       pthread_join(idP[index], NULL);
   }
   
   for (index = 0; index < NC; index++)
   {
       /* code */
       pthread_join(idC[index], NULL);
   }
   

    pthread_exit(NULL);
}