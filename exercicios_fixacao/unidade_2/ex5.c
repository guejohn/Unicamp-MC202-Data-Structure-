/**

Lista de exercícios de fixação

Questão 5) Escreva uma função que calcule o produto de duas matrizes

**/

#include <stdio.h>
#define MAX 10

int main()
{
    int m, n, i, j, c, d, k;
    int soma = 0;
    int matriz1[MAX][MAX], matriz2[MAX][MAX], resultado[MAX][MAX];

    printf("Número de linhas da primeira matriz: \n");
    scanf("%d", &m);

    printf("Número de colunas da primeira matriz: \n");
    scanf("%d", &n);

    printf("Digite os elementos da primeira matriz: \n");

    for (c = 0; c < m; c++)
    {
        for (d = 0; d < n; d++)
        {
            scanf("%d", &matriz1[c][d]);
        }
    }

    printf("Número de linhas da segunda matriz: \n");
    scanf("%d", &i);

    printf("Número de colunas da primeira matriz: \n");
    scanf("%d", &j);

    if (n != i)
        printf("Não é possível multiplicar! \n");

    else
    {
        printf("Digite os elementos da segunda matriz: \n");

        for (c = 0; c < i; c++)
        {
            for (d = 0; d < j; d++)
            {
                scanf("%d", &matriz2[c][d]);
            }
        }

        for (c = 0; c < m; c++)
        {
            for (d = 0; d < j; d++)
            {
                for (k = 0; k < i; k++)
                {
                    soma = soma + matriz1[c][k] * matriz2[k][d];
                }

                resultado[c][d] = soma;

                soma = 0;
            }
        }

        printf("O produto das matrizes é igual a:\n\n");

        for (c = 0; c < m; c++)
        {
            for (d = 0; d < j; d++)
            {
                printf("%d\t", resultado[c][d]);
            }
            printf("\n");
        }
    }

    return 0;
}