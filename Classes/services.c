#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {

  pid_t newId = fork();

  if (newId > 0) {

    sleep(20);

    exit(0);

  }else{

    sleep(100); //ZOMBIE EXAMPLE

  }

  return 0;

}
