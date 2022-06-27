#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "busca.h"

p_noo cria_no_ofertas(char *nome_empresa, float preco)
{
    /* Cria e aloca dinamicamente um novo nó de oferta e retorna o seu endereço */

    p_noo novo_noo = malloc(sizeof(struct no_oferta));
    strcpy(novo_noo->nome_empresa, nome_empresa);
    novo_noo->preco_produto = preco;
    novo_noo->esq = NULL;
    novo_noo->dir = NULL;
    return novo_noo;
}
p_noc cria_no_codigo(int codigo)
{
    /* Cria e aloca dinamicamente um novo nó de código e retorna o seu endereço */

    p_noc novo_noc = malloc(sizeof(struct no_codigo));
    novo_noc->codigo_produto = codigo;
    novo_noc->esq = NULL;
    novo_noc->dir = NULL;
    novo_noc->raiz_ofertas = NULL;

    return novo_noc;
}
p_noo insere_oferta(p_noo raiz, char *nome_empresa, float preco)
{
    /*Insere a nova oferta, que inclui o nome da empresa e o preço do produto, na árvore binária de busca de ofertas 
    - representada por 'raiz' - e retorna a raiz da árvore com a nova oferta inclusa. */

    p_noo novo;

    if (raiz == NULL)
    {
        novo = cria_no_ofertas(nome_empresa, preco);
        return novo;
    }
    else if (strcmp(nome_empresa, raiz->nome_empresa) < 0)
    {
        raiz->esq = insere_oferta(raiz->esq, nome_empresa, preco);
    }
    else
    {
        raiz->dir = insere_oferta(raiz->dir, nome_empresa, preco);
    }
    return raiz;
}

p_noc insere_codigo(p_noc raiz, int codigo)
{
    /*Insere 'codigo' na árvore binária de busca de códigos, representada por 'raiz', e retorna a raiz da árvore
    com o novo código incluso. Se o código já estiver presente na árvore, simplesmente retorna a raiz original */

    p_noc novo;

    if (raiz == NULL)
    {
        novo = cria_no_codigo(codigo);
        return novo;
    }
    else if (codigo == raiz->codigo_produto)
    {
        return raiz;
    }
    else if (codigo < raiz->codigo_produto)
    {
        raiz->esq = insere_codigo(raiz->esq, codigo);
    }
    else
    {
        raiz->dir = insere_codigo(raiz->dir, codigo);
    }
    return raiz;
}
p_noc busca_no(p_noc raiz, int codigo)
{
    /* Busca o nó de código igual a 'codigo' na árvore binária de busca de códigos, e retorna o seu endereço.
    Se o código não existir na árvore, retornará NULL */

    while (raiz != NULL && codigo != raiz->codigo_produto)
        if (codigo < raiz->codigo_produto)
        {
            raiz = raiz->esq;
        }
        else
        {
            raiz = raiz->dir;
        }
    return raiz;
}
p_noc recebe_anuncios(int num_anuncios, p_noc raiz_c)
{
    /*Lê os 'num_anuncios' anuncios, compostos pelo nome da empresa, o código do produto e o preço do produto. 
    Depois, insere o código de cada produto em uma árvore de raiz igual a 'raiz_c' e insere as ofertas,
    com o nome da empresa e o preço do produto, em uma árvore de ofertas daquele código de produto. */

    int codigo_produto;
    float preco;
    char nome_empresa[30];
    p_noc no_atual;

    for (int i = 0; i < num_anuncios; i++)
    {
        scanf("%s %d %f", nome_empresa, &codigo_produto, &preco);
        raiz_c = insere_codigo(raiz_c, codigo_produto);
        no_atual = busca_no(raiz_c, codigo_produto);
        no_atual->raiz_ofertas = insere_oferta(no_atual->raiz_ofertas, nome_empresa, preco);
    }
    return raiz_c;
}

void imprime_ordenado(p_noo raiz, int codigo_produto, float valor_oferta, int *oferta_encontrada)
{ 
    /* Imprime, em ordem lexicográfica do nome de empresa, todas as ofertas da árvore binária de busca de ofertas - representada por 'raiz' - que satisfaçam a condição do preço do produto ser até 110% do valor de oferta, no formato
    "{nome_empresa} {codigo produto} {valor_produto}" */

    if (raiz != NULL)
    {
        imprime_ordenado(raiz->esq, codigo_produto, valor_oferta, oferta_encontrada);
        if (raiz->preco_produto <= valor_oferta * 1.1)
        {
            printf("%s %d %.2f\n", raiz->nome_empresa, codigo_produto, raiz->preco_produto);
            *oferta_encontrada = 1;
        }
        imprime_ordenado(raiz->dir, codigo_produto, valor_oferta, oferta_encontrada);
    }
}
void busca_ofertas(int num_buscas, p_noc raiz_c)
{
    /*Lê 'num_buscas' buscas e mostra as ofertas encontradas, no formato "{nome_empresa} {codigo_produto} {preco_produto}", de acordo com o codigo do produto e o valor da oferta lidos (considera-se dentro do valor da oferta um valor de produto até
    110% do valor de oferta).
    Se nenhuma oferta for encontrada, mostra-se "nenhuma boa oferta foi encontrada" */

    int codigo_produto, oferta_encontrada;
    float valor_oferta;
    p_noc no_atual;

    for (int i = 0; i < num_buscas; i++)
    {
        oferta_encontrada = 0;
        scanf("%d %f", &codigo_produto, &valor_oferta);
        no_atual = busca_no(raiz_c, codigo_produto);
        printf("OFERTAS para %d:\n", codigo_produto);
        if (no_atual != NULL)
        {
            imprime_ordenado(no_atual->raiz_ofertas, codigo_produto, valor_oferta, &oferta_encontrada);
        }
        if (oferta_encontrada == 0)
        {
            printf("nenhuma boa oferta foi encontrada\n");
        }
        printf("\n");
    }
}
void destroi_arvore_ofertas(p_noo raiz)
{
    /*Destrói a árvore binária de ofertas, liberando o espaço de todos os seus nós.*/

    if (raiz != NULL)
    {
        destroi_arvore_ofertas(raiz->dir);
        destroi_arvore_ofertas(raiz->esq);
        free(raiz);
    }
}
void destroi_arvore(p_noc raiz)
{
    /*Destrói a árvore binária de códigos e a de ofertas, liberando todos os seus nós*/

    if (raiz != NULL)
    {
        destroi_arvore_ofertas(raiz->raiz_ofertas);
        destroi_arvore(raiz->dir);
        destroi_arvore(raiz->esq);
        free(raiz);
    }
}