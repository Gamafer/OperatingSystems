/*
 *  Fernando Garrote
 *  A01027503
 *  Critical Section
 *  To compile: gcc CriticalSection.c -o th -lpthread
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int valor = 0;

void *CritSection(void *args){

  long *id = (long *)args;

  //printf("Se ha insertado la variable %d\n", valor);

  printf("Process %ld is entering critical section\n", *id);
  printf("Process %ld is in the Critical Section\n", *id);

  valor++;
  sleep(3);

  printf("Process %ld is leaving the critical section\n", *id);

}

int main(){

  pthread_t p1;
  pthread_t p2;
/*
  int a = 1;
  int b = 2;
*/
  void* apuntador1;
  void* apuntador2;

  pthread_create(&p1, NULL, CritSection, (void *) apuntador1);
  pthread_create(&p2, NULL, CritSection, (void *) apuntador2);

  pthread_join(p1, NULL);
  pthread_join(p2, NULL);

  return 0;

}
