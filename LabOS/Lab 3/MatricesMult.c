/*
 *  Fernando Garrote A01027503
 * 
 *  Matrix multiplications
 * 
 */
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>

#define K 2

#define M 3
#define N 3

int A[M][K] = {{1,4}, {2,5}, {3,6}};
int B[K][N] = {{8,7,6}, {5,4,3}};
int C[M][N];

struct p{
  int i;
  int j;
};

/*
void *suma(void* arg){

  struct p *param = (struct p*) arg;
  int fila = param->i;      //se va a signar el valor de i en la fila, debido a que lee el valor de memoria de i
  int columna = param->j;

  C[fila][columna] = A[fila][columna] + B[fila][columna];

};
*/

void *mult(void* arg){

  struct p *param = (struct p*) arg;

    for (int x = 0; x < M; x++)
    {
        for (int y = 0; y < N; y++)
        {
            C[x][y] = 0;
            for (int z = 0; z < K; z++)
            {
                C[x][y] += A[x][z] * B[z][y];
            }
            
        }
        
    }

};

void PrintMatrix(){
  for (int filas = 0; filas < M; filas++) {

    for (int columnas = 0; columnas < N; columnas++) {
      printf("%d - ",C[filas][columnas]);
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

      pthread_create(&workers[filas][columnas], NULL, mult, (void *)temp);
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
