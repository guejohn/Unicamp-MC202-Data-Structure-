/**

Lista de exercícios de fixação

Questão 2) Escreva uma função iterativa para decidir se uma matriz é simétrica

**/

#include <stdio.h>
#define MAX 3 // considerando nesse caso uma matriz 3x3

int main()
{
    int A[MAX][MAX];  
    int T[MAX][MAX];

    int linha, coluna, simetrica;

    /* Lendo a matriz */

    printf("Digite uma matriz de tamanho 3x3: \n");
    
    for(linha=0; linha<MAX; linha++)
    {
        for(coluna=0; coluna<MAX; coluna++)
        {
            scanf("%d", &A[linha][coluna]);
        }
    }

    /* Encontrando a matriz transposta de A */

    for(linha=0; linha<MAX; linha++)
    {
        for(coluna=0; coluna<MAX; coluna++)
        {
            /* Cada coluna de A para cada linha de T */

            T[linha][coluna] = A[coluna][linha];
        }
    }


    /* Verificando se é igual à transposta */

    simetrica = 1;

    for(linha=0; linha<MAX && simetrica; linha++)
    {
        for(coluna=0; coluna<MAX; coluna++)
        {
            /* Se é diferente */

            if(A[linha][coluna] != T[linha][coluna])
            {
                simetrica = 0;
                break;
            }
        }
    }

    /* Se é igual */

    if(simetrica == 1)
    {
        printf("\n A matriz apresentada abaixo é simétrica: \n");

        for(linha=0; linha<MAX; linha++)
        {
            for(coluna=0; coluna<MAX; coluna++)
            {
                printf("%d ", A[linha][coluna]);
            }

            printf("\n");
        }
    }
    else
    {
        printf("\nA matriz apresentada não é simétrica");
    }

    return 0;
}