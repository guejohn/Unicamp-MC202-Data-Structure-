#include <stdio.h>
#include <stdlib.h>

int retorna_indice(char array[], int tamanho_array, char elemento) {
    
  /* Retorna o índice de 'elemento' no 'array'. Caso não conste, retorna 0 */

  for (int i = 0; i < tamanho_array; i++) {

    if (array[i] == elemento) {
      return i;
    }
  }
  return 0;
}

void inicializa_DNA(char DNA_transcrito[], int tamanho_DNA){

    /* inicializa todos os chars do DNA com "." */
    for(int c = 0; c < tamanho_DNA; c++){
        DNA_transcrito[c] = '.';
    }
}
void mostra_transcricao(int tamanho_DNA, int ID[], char DNA_alienigena[], char DNA_transcrito[]){
    /*
    Mostra transcricao no seguinte formato:

    ID: 	0	1	0	0	1	2
    DNA:	A	A	C	D	C	C
    	    |	|	|	|	|	|
    RNA: 	Y	Y	X	W	X	X
    */    
    printf("ID:  ");

    for(int c = 0; c < tamanho_DNA; c++){
        printf("%d ", ID[c]);
    }

    printf("\n");

    printf("DNA: ");
    for(int c = 0; c < tamanho_DNA; c++){
        printf("%c ", DNA_alienigena[c]);
    }

    printf("\n     ");
    
    for(int c = 0; c < (tamanho_DNA); c++){
        printf("| ");
    }

    printf("\nRNA: ");

    for(int c = 0; c < tamanho_DNA; c++){
        printf("%c ", DNA_transcrito[c]);
    }
}

int frequencia(char array[], int tamanho_array, char elemento) {

  /* Dado um array de chars, retorna quantas vezes 'elemento' aparece. */

  int contador = 0;

  for (int i = 0; i < tamanho_array; i++) {
    if (array[i]==elemento) {
      contador++;
    }
  }
  return contador;
}


void transcreve(char DNA_transcrito[], char bases_RNA[], char bases_DNA[], char DNA_alienigena[], int tamanho_DNA, int ID[]){
    
    /* transcreve o DNA alienigena para RNA */

    for(int i = 0; i < tamanho_DNA; i++){
        DNA_transcrito[i] = bases_RNA[retorna_indice(bases_DNA, 14, DNA_alienigena[i])];
        ID[i] = frequencia(DNA_transcrito, tamanho_DNA, DNA_transcrito[i])-1;
    }
}

int main()
{
    char bases_DNA[14], bases_RNA[14];
    int tamanho_DNA,*ID;
    char *DNA_alienigena, *DNA_transcrito;

    scanf("%s", bases_DNA); 
    scanf("%s", bases_RNA); 
    scanf("%d", &tamanho_DNA);

    DNA_alienigena = malloc((tamanho_DNA+1) * sizeof(char));
    DNA_transcrito = malloc((tamanho_DNA+1) * sizeof(char));
    ID = malloc(tamanho_DNA * sizeof(int));

    inicializa_DNA(DNA_transcrito, tamanho_DNA);
    scanf("%s", DNA_alienigena);

    transcreve(DNA_transcrito, bases_RNA, bases_DNA, DNA_alienigena, tamanho_DNA, ID);
    mostra_transcricao(tamanho_DNA, ID, DNA_alienigena, DNA_transcrito);

    free(DNA_alienigena);
    free(DNA_transcrito);
    free(ID);
    return 0;
}
