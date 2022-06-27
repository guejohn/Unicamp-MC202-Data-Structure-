#include <stdio.h>
#include <string.h>
#define MAX 100

int retorna_indice(char lista[], int tamanho_lista, char elemento) {
    
  /* Retorna o índice de 'elemento' na 'lista'. Caso não conste, retorna 0 */

  for (int i = 0; i < tamanho_lista; i++) {

    if (lista[i] == elemento) {

      return i;
    }
  }
  return 0;
}

void separa_nome_sobrenome(char nomes_completos[][MAX], char nomes[][MAX], char sobrenomes[][MAX], int tamanho_lista) {

  /* Dada uma lista de nomes completos contendo '_' como divisor, separa o nome completo em nome e sobrenome e
  guarda, respectivamente, nas listas 'nomes' e 'sobrenomes. */

  int indice;

  for (int c = 0; c < tamanho_lista; c++) {

    indice = retorna_indice(nomes_completos[c], strlen(nomes_completos[c]), '_');

    for (int i = 0; i < indice; i++) {
      nomes[c][i] = nomes_completos[c][i];
    }

    for (int i = 0; i < strlen(nomes_completos[c]); i++) {
      sobrenomes[c][i] = nomes_completos[c][(indice + 1) + i];
    }
  }

}

int tamanho_vetor_inteiros(int vetor[]) {

  /* Dado um array de números inteiros inicialmente inicializado com valores -1, retorna o seu tamanho. */

  int i = 0;

  while (i <= MAX) {
    if (vetor[i] == -1) {
      return i;
    }
    i++;
  }
  return MAX;
}

void ordena_lista(char lista[][MAX], int tamanho_lista) {

  /* Dada uma lista de strings, ordena os seus elementos lexicograficamente */

  char aux[MAX];

  for (int i = 0; i < tamanho_lista; i++) {
    for (int j = 0; j < tamanho_lista; j++) {
      if (strcmp(lista[j], lista[i]) > 0) {

        strcpy(aux, lista[i]);
        strcpy(lista[i], lista[j]);
        strcpy(lista[j], aux);
      }
    }
  }
}

int frequencia_lista(char lista[][MAX], int tamanho_lista, char string[]) {

  /* Dada uma lista de strings, retorna quantas vezes 'string' aparece na lista. */

  int contador = 0;

  for (int i = 0; i < tamanho_lista; i++) {
    if (strcmp(lista[i], string) == 0) {
      contador++;
    }
  }
  return contador;
}

int numero_nao_presente(int lista[MAX], int numero) {

  /* Verifica se um numero está contido em uma lista de numeros. Se não estiver, retorna 1. Do contrário, retorna 0. */

  for (int i = 0; i < tamanho_vetor_inteiros(lista); i++) {
    if (lista[i] == numero) {
      return 0;
    }
  }
  return 1;
}

void verifica_homonimos(char nomes[][MAX], int indices_homonimos[], int num_nomes) {

  /* Verifica, dentro de uma lista de nomes, aqueles que são homônimos e guarda os seus indices, referentes à lista 'nomes',
  na lista 'indices_homonimos' */

  for (int i = 0; i < num_nomes; i++) {
    if (frequencia_lista(nomes, num_nomes, nomes[i]) > 1) {
      for (int j = 0; j < num_nomes; j++) {
        if ((strcmp(nomes[i], nomes[j]) == 0) && (numero_nao_presente(indices_homonimos, j) == 1)) {
          indices_homonimos[tamanho_vetor_inteiros(indices_homonimos)] = j;
        }
      }
    }
  }
}

void inicializa_lista_inteiros(int lista_indices[]) {

  /* Dada uma lista de inteiros, inicializa todos os seus elementos com o valor -1 */

  for (int i = 0; i < MAX; i++) {
    lista_indices[i] = -1;
  }
}

void mostra_nomes(int indices_homonimos[], char nomes_completos[][MAX]) {

  /* Dada uma lista de nomes, exibe um por linha */

  for (int c = 0; c < tamanho_vetor_inteiros(indices_homonimos); c++) {
    printf("%s\n", nomes_completos[indices_homonimos[c]]);
  }
}

void le_nomes(char nomes_completos[][MAX], int num_nomes) {

  /* Lê nomes da entrada padrão 'num_nomes' vezes e os guarda em uma lista 'nomes_completos' */

  for (int i = 0; i < num_nomes; i++) {
    scanf("%s", nomes_completos[i]);

  }
}

int main() {

  int num_estudantes, indices_homonimos[MAX];
  char nomes_completos[MAX][MAX], nomes[MAX][MAX], sobrenomes[MAX][MAX], opcao[MAX];

  scanf("%d", &num_estudantes);
  scanf("%s ", opcao);

  le_nomes(nomes_completos, num_estudantes);
  ordena_lista(nomes_completos, num_estudantes);
  separa_nome_sobrenome(nomes_completos, nomes, sobrenomes, num_estudantes);
  inicializa_lista_inteiros(indices_homonimos);
  verifica_homonimos(nomes, indices_homonimos, num_estudantes);
  mostra_nomes(indices_homonimos, nomes_completos);

}