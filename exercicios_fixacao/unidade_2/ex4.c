/**

Lista de exercícios de fixação

Questão 4) Escreva uma função que calcule o determinante de uma matriz 3×3

**/

#include <stdio.h>

int main()
{

    int a[3][3], i, j, determinante;

    printf("Digite os nove elementos da matriz 3x3: ");

    for (i = 0; i < 3; i++)
    {

        for (j = 0; j < 3; j++)
        {

            scanf("%d", &a[i][j]);
        }
    }

    printf("\nA matriz\n");

    for (i = 0; i < 3; i++)
    {

        printf("\n");

        for (j = 0; j < 3; j++)

            printf("%d\t", a[i][j]);
    }

    determinante = a[0][0] * ((a[1][1] * a[2][2]) - (a[2][1] * a[1][2])) - a[0][1] * (a[1][0]* a[2][2] - a[2][0] * a[1][2]) + a[0][2] * (a[1][0] * a[2][1] - a[2][0] * a[1][1]);

    printf("\n\n tem determinante igual a %d", determinante);

    return 0;
}