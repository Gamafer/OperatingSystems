#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int g = 0;
pthread_mutex_t lockVariable = PTHREAD_MUTEX_INITIALIZER;



void *function(void *args){
    
    int *id = (int *) args;
    
    printf("Thread %d entering critical section\n", *id);
    pthread_mutex_t (&lockVariable);
    printf("Thread %d in critical section\n", *id);
    g++;    //Wants to modify the 'g' variable
    sleep(3);
    printf("Thread %d outside critical section\n", *id);
    pthread_mutex_unlock(&lockVariable);

};

int main(){

    pthread_t tid1, tid2;

    int id1 = 1;
    int id2 = 2;

    pthread_create(&tid1, NULL, function, (void *) &id1);
    pthread_create(&tid2, NULL, function, (void *) &id2);

    pthread_join(tid1);
    pthread_join(tid2);

    return 0;
}