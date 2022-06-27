#include <stdio.h>

int main()
{
    /* Questão 5:
    Faça um algoritmo que leia um dado número X inteiro
    e verifique se esse número é divisível por 3 e 5 simultaneamente */

    int x;
    scanf("%d", &x);

    if (x % 3 == 0 && x % 5 == 0)
    {
        printf("É divisível\n");
    }
    else
    {
        printf("Não é divisível\n");
    }

    return 0;
}
