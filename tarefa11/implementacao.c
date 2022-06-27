#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "piramide.h"

void remunera_niveis(p_no no)
{
    /* Remunera até seis níveis da pirâmide (representada por uma árvore), seguindo a seguinte regra:
    Cada um dos dois novos participantes paga 6% do seu capital para o recrutador, que depois paga 5%
    do seu capital para seu próprio recrutador, que depois paga 4% e assim por diante... */

    float percentual = 6;
    p_no no_atual = no;

    while (1)
    {
        if (no_atual->pai == NULL || percentual == 0)
        {
            break;
        }
        else
        {
            if (percentual == 6)
            {
                no_atual->pai->valor += (no_atual->pai->esq->valor * (percentual / 100)) + (no_atual->pai->dir->valor * (percentual / 100));
                no_atual->pai->esq->valor = (no_atual->pai->esq->valor * (1 - (percentual / 100)));
                no_atual->pai->dir->valor = (no_atual->pai->dir->valor * (1 - (percentual / 100)));
            }
            else
            {
                no_atual->pai->valor += (no_atual->valor * (percentual / 100));
                no_atual->valor = (no_atual->valor * (1 - (percentual / 100)));
            }
            no_atual = no_atual->pai;
            percentual--;
        }
    }
}
void insere(p_no filho, p_no pai)
{
    /* Insere o nó 'filho' abaixo do nó 'pai' e acrescenta ao valor de investimento do 'filho'
    a bonificação de 10% de seu investimento inicial, que é descontado do nó 'pai' */

    filho->pai = pai;

    if (pai->esq == NULL)
    {
        pai->esq = filho;
    }
    else
    {
        pai->dir = filho;
    }
    pai->valor -= (filho->valor * 0.1);
    filho->valor += (filho->valor * 0.1);
}

int calcula_altura(p_no raiz)
{   
    /* Calcula a altura de uma árvore e retorna o seu valor */

    if (raiz == NULL)
    {
        return 0;
    }
    else
    {
        int altura_esq = calcula_altura(raiz->esq);
        int altura_dir = calcula_altura(raiz->dir);

        if (altura_esq > altura_dir)
        {
            return (altura_esq + 1);
        }
        else
        {
            return (altura_dir + 1);
        }
    }
}

void imprime_nos_nivel(p_no raiz, int nivel)
{ 
    /* Exibe todos os nós do nível 'nivel' no formato
    "[nome_do_no valor_do_no]", para cada nó do nível,
    da esquerda para a direita */

    if (raiz == NULL)
    {
        return;
    }
    else if (nivel == 1)
    {
        printf("[%s %.2f] ", raiz->nome, raiz->valor);
    }
    else if (nivel > 1)
    {
        imprime_nos_nivel(raiz->esq, nivel - 1);
        imprime_nos_nivel(raiz->dir, nivel - 1);
    }
}

void mostra_nos_arvore(p_no raiz)
{   
    /*Mostra todos os nós de uma árvore, por nível.*/

    int altura = calcula_altura(raiz);
    for (int i = 1; i <= altura; i++)
    {
        printf("Nivel %d: ", i);
        imprime_nos_nivel(raiz, i);
        printf("\n");
    }
    printf("\n");
}

p_no busca_no(p_no raiz, char *nome)
{   
    /*Busca o nó contido na árvore com o nome igual a 'nome' e retorna o seu endereço*/

    p_no raiz_esq, raiz_dir;

    if (raiz == NULL || strcmp(nome, raiz->nome) == 0)
    {
        return raiz;
    }
    else
    {
        raiz_esq = busca_no(raiz->esq, nome);
        if (raiz_esq != NULL)
        {
            return raiz_esq;
        }
        raiz_dir = busca_no(raiz->dir, nome);
        return raiz_dir;
    }
}

p_no cria_no(char *nome, float valor)
{
    /*Cria e aloca um nó dinamicamente, como nome igual a 'nome' e valor igual a 'valor, e retorna o seu endereço*/

    p_no novo = malloc(sizeof(struct no));
    strcpy(novo->nome, nome);
    novo->valor = valor;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = NULL;

    return novo;
}

void destroi_arvore(p_no raiz)
{
    /*Destrói uma árvore binária, liberando o espaço de todos os seus nós.*/

    if (raiz != NULL)
    {
        destroi_arvore(raiz->dir);
        destroi_arvore(raiz->esq);
        free(raiz);
    }
}