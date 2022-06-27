#include <stdio.h>

int calcula_inverso(int num)
{   
    /* Calcula o num_invertido de um número.
    Exemplo:
    1234 -> 4321 */

    int num_invertido = 0, resto;

    while (num != 0)
    {
        resto = num % 10;
        num_invertido = num_invertido * 10 + resto;
        num /= 10;
    }
    return num_invertido;
}

int main()
{
    /* Questão 2:
    Um capicua é um número palíndromo, i.e., um número decimal que lido da esquerda para a direita
    é o mesmo que quando lido da direita para a esquerda. Exemplos:
    •  10201
    •  2002
    •  565
    •  99
    •  7
    Faça  um  algoritmo  que  leia  um  número  inteiro  arbitrário  e  verifique  se  esse  número
    é  ou  não  capicua utilizando apenas operações para números inteiros. */

    int num, num_invertido, resto;

    printf("Digite um número inteiro: ");
    scanf("%d", &num);

    num_invertido = calcula_inverso(num);

    if (num == num_invertido)
    {
        printf("O número é um capicua!\n");
    }
    else
    {
        printf("O número não é um capicua!\n");
    }

    return 0;
}
