/*
 *  Fernando Garrote
 *  A01027503
 *  Threads example
 *  To compile: gcc threads.c -o th -lpthread
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *printMessage(void *m){
  char *message = (char *)m;
  sleep(10);
  printf("%s\n", message);
}

int main() {

  pthread_t tId;
  char *m = "Hello world";
  pthread_create(&tId, NULL, printMessage, (void *) m);
  printf("Created thread: %ld\n", tId);
  pthread_join(tId, NULL);

  return 0;
}
