#include <stdio.h>
#define max 10000

void copia_lista(int lista1[], int lista2[], int tamanho)
{
    /* Copia todos os elementos do array 'lista2' para o array 'lista1' */

    for (int i = 0; i < tamanho; i++)
    {
        lista1[i] = lista2[i];
    }
}

int retorna_indice(int lista[], int tamanho_lista, int elemento)
{
    /*Retorna o índice de 'elemento' na 'lista' de tamanho 'tamanho' */

    for (int i = 0; i < tamanho_lista; i++)
    {
        if (lista[i] == elemento)
        {
            return i;
        }
    }
    return 0;
}

void muda_participante(int fila[], int primeiro, int segundo, int tamanho)
{
    /* Altera a posição de 'primeiro' no vetor, colocando-o como o próximo elemento de 'segundo',
    representando que o participante de número 'primeiro' resolveu esperar pelo participante de número 'segundo'.  */

    int indice_primeiro, indice_segundo, nova_fila[max];
    copia_lista(nova_fila, fila, tamanho);

    indice_primeiro = retorna_indice(fila, tamanho, primeiro);
    indice_segundo = retorna_indice(fila, tamanho, segundo);

    int i = indice_primeiro;

    while (i <= indice_segundo)
    {
        if (i != indice_segundo)
        {
            nova_fila[i] = fila[i + 1];
        }
        else
        {
            nova_fila[i] = primeiro;
        }
        i += 1;
    }
    copia_lista(fila, nova_fila, tamanho);
}

void inverte_ordem(int fila[], int primeiro, int segundo, int tamanho)
{
    /*Dado um array 'fila', inverte a ordem dos elementos de 'primeiro' até 'último'*/

    int indice_primeiro, indice_segundo, nova_fila[max];
    copia_lista(nova_fila, fila, tamanho);

    indice_primeiro = retorna_indice(fila, tamanho, primeiro);
    indice_segundo = retorna_indice(fila, tamanho, segundo);

    int i = indice_primeiro;
    int j = indice_segundo;

    while (i <= indice_segundo)
    {
        nova_fila[i] = fila[j];
        i += 1;
        j -= 1;
    }

    copia_lista(fila, nova_fila, tamanho);
}

void criar_fila(int tamanho, int fila[])
{
    /* inicializa o array 'fila' com os números de 1 até 'tamanho' */

    for (int i = 0; i < tamanho; i++)
    {
        fila[i] = i + 1;
    }
}

void altera_fila(int num_participantes, int num_movimentos, int fila[])
{   
    /* Altera a fila de acordo com o tipo de movimento:
    1 - Quando um grupo de amigos, que estão um atrás do outro, resolve conversar e voltam à fila na ordem inversa;
    2- Quando uma pessoa resolve esperar por outra. */

    int tipo_movimento, primeiro, segundo;

    for (int i = 0; i < num_movimentos; i++)
    {
        scanf("%d", &tipo_movimento);
        scanf(" %d %d", &primeiro, &segundo);

        if (tipo_movimento == 1)
        {
            inverte_ordem(fila, primeiro, segundo, num_participantes);
        }
        else if (tipo_movimento == 2)
        {
            muda_participante(fila, primeiro, segundo, num_participantes);
        }
    }
}

void mostra_fila(int fila[], int tamanho){

    /* Dado um array 'fila', imprime todos os seus elementos separados por ' ' */
    
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", fila[i]);
    }
}

int main()
{
    int num_participantes, num_movimentos;

    scanf("%d", &num_participantes);
    scanf("%d", &num_movimentos);

    int fila[max];
    criar_fila(num_participantes, fila);
    altera_fila(num_participantes, num_movimentos, fila);
    mostra_fila(fila, num_participantes);

    return 0;
}
