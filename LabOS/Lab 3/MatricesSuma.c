/*
 *  Fernando Garrote A01027503
 * 
 *  Matrix additions
 * 
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define M 3
#define N 3

int A[M][N] = {{1,2,3}, {4,5,6}};
int B[M][N] = {{7,8,9}, {10,11,12}};
int C[M][N];

struct p{
  int i;
  int j;
};

void *suma(void* arg){

  struct p *param = (struct p*) arg;
  int fila = param->i;      //se va a signar el valor de i en la fila, debido a que lee el valor de memoria de i
  int columna = param->j;

  C[fila][columna] = A[fila][columna] + B[fila][columna];

};

void PrintMatrix(){
  for (int filas = 0; filas < M; filas++) {

    for (int columnas = 0; columnas < N; columnas++) {
      printf(" %d -",C[filas][columnas]);
    }
      printf("\n");
  }
}

int main() {

  pthread_t workers[M][N];

  for (int filas = 0; filas < M; filas++) {

    for (int columnas = 0; columnas < N; columnas++) {
      struct p *temp = malloc(sizeof(struct p));

      temp->i = filas;
      temp-> j = columnas;

      pthread_create(&workers[filas][columnas], NULL, suma, (void *)temp);
    }
      printf("\n");
  }

  for (int filas = 0; filas < M; filas++) {
    for (int columnas = 0; columnas < N; columnas++) {
        pthread_join(workers[filas][columnas], NULL);
    }
  }

  PrintMatrix();

  return 0;
}
