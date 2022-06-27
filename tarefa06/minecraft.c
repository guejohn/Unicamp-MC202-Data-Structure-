#include <stdio.h>
#include <stdlib.h>
#include "minecraft.h"

void mostrar_informacoes(int *qtdBlocos, double tempo_total, int *qtdDiamante, int *qtdOuro, int *qtdFerro) {

  /* Mostra ao usuário o total de blocos a serem minerados, o tempo total (em segundos) para a sua mineração e a quantidade
  de blocos de diamantes, de ouro e de ferros disponíveis, respectivamente */

  printf("Total de Blocos: %d\n", *qtdBlocos);
  printf("Tempo total: %.2fs\n", tempo_total);
  printf("Diamantes: %d\n", *qtdDiamante);
  printf("Ouros: %d\n", *qtdOuro);
  printf("Ferros: %d\n", *qtdFerro);
}

double explorarMundo(Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco, int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos) {
  
  /* Explora o mapa de um mundo e devolve o tempo
   necessário para minerar todo ele. Além disso,
   devolve a quantidade de alguns minérios de
   interesse (diamante, ouro e ferro) */

  char tipo_bloco;
  double tempo_total = 0;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      for (int y = 0; y < 256; y++) {

        tipo_bloco = mundo[i][j][y].tipo;

        if ((tipo_bloco != 'V') && (tipo_bloco != 'A') && (tipo_bloco != 'L')) {

          *qtdBlocos += 1;
          tempo_total += tempoPorBloco;

          if (tipo_bloco == 'D') {
            *qtdDiamante += 1;
          }
          else if (tipo_bloco == 'O') {
            *qtdOuro += 1;
          }
          else if (tipo_bloco == 'F') {
            *qtdFerro += 1;
          }
        }
      }
    }
  }
  return tempo_total;
}

Bloco ***criarMundo(int m, int n, int **altitudes, int seed) {

  /* Cria um novo mundo representado por uma matriz
    de blocos alocada dinamicamente */

  int M;

  Bloco ***mundo = malloc(m * sizeof(Bloco **));

  if (mundo == NULL) {
    printf("Sem memória");
    exit(0);
  }

  for (int i = 0; i < m; i++) {
    mundo[i] = malloc(n * sizeof(Bloco *));

    if (mundo[i] == NULL) {
      printf("Sem memória");
      exit(0);
    }

    for (int j = 0; j < n; j++) {
      mundo[i][j] = malloc(256 * sizeof(Bloco));
      if (mundo[i][j] == NULL) {
        printf("Sem memória");
        exit(0);
      }
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      for (int y = 0; y < 256; y++) {

        if (y > altitudes[i][j]) {
          mundo[i][j][y].tipo = 'V';
        }
        else {
            
          M = (seed * (202 + i + y + j) + i + y + j) % 33;

          if (M == 0) {
            mundo[i][j][y].tipo = 'D';
          } 
          else if (M == 1 || M == 2) {
            mundo[i][j][y].tipo = 'O';
          }
          else if (M >= 3 && M <= 5) {
            mundo[i][j][y].tipo = 'F';
          }
          else if (M >= 6 && M <= 11) {
            mundo[i][j][y].tipo = 'P';
          }
          else if (M >= 12 && M <= 20) {
            mundo[i][j][y].tipo = 'T';
          }
          else if (M >= 21 && M <= 23) {
            mundo[i][j][y].tipo = 'V';
          }
          else if (M >= 24 && M <= 28) {
            mundo[i][j][y].tipo = 'A';
          }
          else if (M >= 29 && M <= 32) {
            mundo[i][j][y].tipo = 'L';
          }
        }
      }
    }
  }
  return mundo;
}
int **calcularAltitudes(int m, int n, int seed) {
    
/* Cria uma matriz de altitudes representando
   o relevo de um mundo. */

  int **altitudes = malloc(m * sizeof(int * ));

  for (int i = 0; i < m; i++) {
    altitudes[i] = malloc(n * sizeof(int));
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      altitudes[i][j] = (seed * (202 + i + j) + 12345 + i + j) % 256;
    }
  }

  return altitudes;
}

void liberar_memoria(int m, int n, Bloco ***mundo, int **altitudes) {
  
  /* Libera a memória que foi alocada dinamicamente durante a execução do programa */

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      free(mundo[i][j]);
    }
    free(mundo[i]);
  }
  free(mundo);

  for (int i = 0; i < m; i++) {
    free(altitudes[i]);
  }
  free(altitudes);
}

int main() {

  int m, n, seed;
  double tempoPorBloco, tempo_total;
  int qtdDiamante = 0, qtdOuro = 0, qtdFerro = 0, qtdBlocos = 0;

  scanf("%d %d", &m, &n);
  scanf("%d", &seed);
  scanf("%lf", &tempoPorBloco);

  int **altitudes = calcularAltitudes(m, n, seed);

  Bloco ***mundo = criarMundo(m, n, altitudes, seed);

  tempo_total = explorarMundo(mundo, m, n, altitudes, tempoPorBloco, &qtdDiamante, &qtdOuro, &qtdFerro, &qtdBlocos);

  mostrar_informacoes(&qtdBlocos, tempo_total, &qtdDiamante, &qtdOuro, &qtdFerro);

  liberar_memoria(m, n, mundo, altitudes);

  return 0;
}