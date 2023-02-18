/*
 * Num Arg: Prints Arg forever
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(int argc, char *argv[]) 
{
  char Char[1];

  if (argc!=2) {
    printf("Error in input parameter\n");
    exit(-1);
  }
  strcpy (Char, argv[1]);
  while (1) {
    printf("%s",Char);
  }
}
