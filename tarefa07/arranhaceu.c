#include <stdio.h>
#include <stdlib.h>

void mostra(int **matriz, int tamanho)

/* 
    Imprime uma matriz quadrada, de ordem "tamanho", com seus elementos separados por espaço. 
*/

{
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

int verifica_pistas(int **grade, int **pistas, int tamanho)
{
    /* 
    Verifica se a matriz preenchida está de acordo com as regras das pistas.
    Retorna 1 se sim, 0 se não.
    */

    for (int linha = 0; linha < tamanho; linha++)
    {
        int cont_direita = 1, cont_esquerda = 1, cont_baixo = 1, cont_cima = 1, maior;

        maior = grade[linha][0];
        for (int j = 1; j < tamanho; j++)
        {
            if (grade[linha][j] > maior)
            {
                cont_esquerda += 1;
                maior = grade[linha][j];
            }
        }

        maior = grade[linha][tamanho - 1];
        for (int j = tamanho - 2; j >= 0; j--)
        {
            if (grade[linha][j] > maior)
            {
                cont_direita += 1;
                maior = grade[linha][j];
            }
        }

        maior = grade[0][linha];
        for (int i = 1; i < tamanho; i++)
        {
            if (grade[i][linha] > maior)
            {
                cont_cima += 1;
                maior = grade[i][linha];
            }
        }

        maior = grade[tamanho - 1][linha];
        for (int i = tamanho - 2; i >= 0; i--)
        {
            if (grade[i][linha] > maior)
            {
                cont_baixo += 1;
                maior = grade[i][linha];
            }
        }

        if ((cont_cima != pistas[0][linha]) || (cont_direita != pistas[1][linha]) || (cont_baixo != pistas[2][linha]) || (cont_esquerda != pistas[3][linha]))
        {
            return 0;
        }
    }
    return 1;
}

int eh_valido(int **grade, int linha, int coluna, int numero, int tamanho)
{
    /* 
    Verifica se é possível colocar 'numero' na posicao grade[linha][coluna],
    ou seja, se o número já não está presente na coluna ou na linha.
    Retorna 1 se sim, 0 se não.
    */

    for (int i = 0; i < tamanho; i++)
    {
        if (grade[linha][i] == numero)
        {
            return 0;
        }
        if (grade[i][coluna] == numero)
        {
            return 0;
        }
    }

    return 1;
}

int encontra_quadrado_vazio(int **grade, int *linha, int *coluna, int tamanho)
{
    /* 
    Verifica se ainda há algum elemento da grade que não foi preenchido
    (ou seja, que é igual a 0). Se houver, altera o valor de 'linha' e 'coluna' com
    os índices desse elemento e retorna 1. Do contrário, retorna 0.
    */

    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            if (grade[i][j] == 0)
            {
                *linha = i;
                *coluna = j;
                return 1;
            }
        }
    }
    return 0;
}

int resolve_arranha_ceu(int **grade, int **pistas, int tamanho)
{
    /*
    Preenche a matriz recursivamente e utilizando backtracking e retorna 1 quando a matriz satisfizer
    as condições do arranha céu.
    */

    int linha;
    int coluna;

    if (encontra_quadrado_vazio(grade, &linha, &coluna, tamanho) == 0)
    {
        if (verifica_pistas(grade, pistas, tamanho))
        {
            return 1;
        }
        return 0;
    }

    for (int numero = 1; numero <= tamanho; numero++)
    {
        if (eh_valido(grade, linha, coluna, numero, tamanho) == 1)
        {
            grade[linha][coluna] = numero;

            if (resolve_arranha_ceu(grade, pistas, tamanho))
            {
                return 1;
            }
            else
            {
                grade[linha][coluna] = 0;
            }
        }
    }
    return 0;
}

void preenche_parcialmente(int **grade, int **pistas, int tamanho)
{
    /*
    Preenche parcialmente a matriz, isto é, para os casos em que
    a pista é igual a 1 ou igual a "tamanho", já se pode prever como ficará(ão) 1 ou mais elementos da linha
    ou coluna, o que otimiza o processo posterior.
    - O elemento cercado por uma das pistas igual a 1 receberá o valor máximo, ou seja, 'tamanho'.
    - O elemento cercado por uma das pistas igual ao valor máximo, ou seja, igual a 'tamanho',
      terá a linha ou coluna preenchida em ordem crescente de 1 a 'tamanho'.
    */

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {

            if (pistas[i][j] == 1)
            {   
                //se é pista de cima
                if (i == 0)
                {
                    grade[0][j] = tamanho;
                }
                //se é pista da direita
                else if (i == 1)
                {
                    grade[j][tamanho - 1] = tamanho;
                }
                //se é pista de baixo
                else if (i == 2)
                {
                    grade[tamanho - 1][j] = tamanho;
                }
                //se é pista da esquerda
                else if (i == 3)
                {
                    grade[j][0] = tamanho;
                }
            }

            else if (pistas[i][j] == tamanho)
            {
                //se é pista de cima
                if (i == 0)
                {
                    for (int linha = 0; linha < tamanho; linha++)
                    {
                        grade[linha][j] = linha + 1;
                    }
                }
                //se é pista da direita
                else if (i == 1)
                {
                    for (int coluna = 0; coluna < tamanho; coluna++)
                    {
                        grade[j][coluna] = tamanho - coluna;
                    }
                }
                //se é pista de baixo
                else if (i == 2)
                {
                    for (int linha = 0; linha < tamanho; linha++)
                    {
                        grade[linha][j] = tamanho - linha;
                    }
                }
                //se é pista da esquerda
                if (i == 3)
                {
                    for (int coluna = 0; coluna < tamanho; coluna++)
                    {
                        grade[j][coluna] = coluna + 1;
                    }
                }
            }
        }
    }
}
void separa_matriz(int **matriz, int **grade, int **pistas, int tamanho)
{
    /*
    Separa a matriz lida em uma matriz 'grade' e em uma matriz 'pistas'.
    Os índices das linhas das pistas representam as seguintes posições, respectivamente:
    0: cima; 1: direita; 2: baixo; 3: esquerda.
    */

    for (int i = 1; i < tamanho - 1; i++)
    {
        for (int j = 1; j < tamanho - 1; j++)
        {
            grade[i - 1][j - 1] = matriz[i][j];
        }
    }

    for (int j = 0; j < tamanho - 2; j++)
    {
        pistas[0][j] = matriz[0][j + 1];
        pistas[1][j] = matriz[j + 1][tamanho - 1];
        pistas[2][j] = matriz[tamanho - 1][j + 1];
        pistas[3][j] = matriz[j + 1][0];
    }
}

void le_matriz(int **matriz, int tamanho)
{
    /*
    Dado 'tamanho', lê os elementos de uma matriz quadrada de ordem 'tamanho' e os armazena em 'matriz'.
    */

    for (int i = 0; i < tamanho; i++)
    {
        for (int j = 0; j < tamanho; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
}

int **cria_matriz(int num_linhas, int num_colunas)
{
    /*
    Cria e aloca dinamicamente o espaço para uma matriz de num_linhas x num_colunas,
    retornando seu ponteiro.
    */

    int **nova_matriz = malloc((num_linhas) * sizeof(int *));

    if (nova_matriz == NULL)
    {
        printf("Sem memória");
        exit(0);
    }

    for (int i = 0; i < num_linhas; i++)
    {
        nova_matriz[i] = malloc((num_colunas) * sizeof(int));

        if (nova_matriz[i] == NULL)
        {
            printf("Sem memória");
            exit(0);
        }
    }
    return nova_matriz;
}

void libera_memoria(int **matriz_qualquer, int num_linhas)
{
    /* 
    Libera a memória de uma matriz qualquer dada, de acordo com suas 'num_linhas' linhas.
    */

    for (int i = 0; i < num_linhas; i++)
    {
        free(matriz_qualquer[i]);
    }
    free(matriz_qualquer);
}

int main()
{
    int n, **matriz, **grade, **pistas;

    //lendo tamanho da matriz
    scanf("%d", &n);

    //criando as matrizes
    matriz = cria_matriz(n + 2, n + 2);
    pistas = cria_matriz(4, n);
    grade = cria_matriz(n, n);

    //lendo e separando os dados
    le_matriz(matriz, n + 2);
    separa_matriz(matriz, grade, pistas, n + 2);
    preenche_parcialmente(grade, pistas, n);

    //solucionando e exibindo a matriz gerada
    if (resolve_arranha_ceu(grade, pistas, n) == 1)
    {
        mostra(grade, n);
    }

    //liberando a memória das matrizes utilizadas
    libera_memoria(matriz, n + 2);
    libera_memoria(pistas, 4);
    libera_memoria(grade, n);

    return 0;
}