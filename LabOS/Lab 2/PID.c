/***********************************************************
 *
 *  <Fernando Garrote> : <A01027503>
 *
 *  Program to visualize process ids and their children
 *
 **************************************************************/
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/wait.h>
 #include <sys/types.h>

 int main() {

   pid_t anakin = getpid();

   printf("Luke, I am your father, I am: %d\n", anakin);

   sleep(30);

   pid_t luke = fork();

   if (luke > 0) {

     printf("I %d, am your father\n", anakin);

     printf("Noooo, replied %d\n", luke);

     wait(NULL);


   }

   pid_t leia = fork();

   if (leia > 0) {

     printf("Hey I'm your sister %d, remember %d?\n", leia, luke);

     printf("My father is %d\n", anakin);

     sleep(100);

   }

   return 0;
 }
