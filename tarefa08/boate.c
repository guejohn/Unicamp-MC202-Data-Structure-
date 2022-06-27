#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 26

typedef struct no *p_no;
typedef struct lista *p_lista;

struct no
{
    int documento;
    char profissao[MAX];
    char status_vacinacao[13];
    p_no prox;
};

struct lista
{
    p_no inicio;
    p_no lanterna;
    p_no fim;
};

p_lista cria_nova_lista()
{
    /*Cria uma nova lista alocada dinamicamente apontando com inicio, lanterna e fim apontando para NULL*/

    p_lista nova_lista = malloc(sizeof(struct lista));
    nova_lista->inicio = NULL;
    nova_lista->lanterna = NULL;
    nova_lista->fim = NULL;

    return nova_lista;
}

int eh_grupo_prioritario(char *profissao)
{
    /* Se a profissão for igual a "coach", "ex-bbb", "filho-politico", "herdeiro" ou "youtuber-financas", retorna 1.
    Do contrário, retorna 0 */

    if ((strcmp(profissao, "coach") == 0) || (strcmp(profissao, "ex-bbb") == 0) || (strcmp(profissao, "filho-politico") == 0) || (strcmp(profissao, "herdeiro") == 0) || (strcmp(profissao, "youtuber-financas") == 0))
    {
        return 1;
    }
    return 0;
}
p_lista expulsa_nao_vacinados(p_no atual, p_lista lista)
{
    /*Até chegar no fim da lista ou até encontrar uma pessoa vacinada, exclui da lista ligada todas as pessoas
    não vacinadas que estão continuamente atrás de um fiscal */

    if (strcmp(atual->status_vacinacao, "vacinado") == 0)
    {
        return lista;
    }
    else
    {
        if (atual->prox == NULL)
        {
            (lista->lanterna)->prox = NULL;
            lista->fim = lista->lanterna;
            free(atual);
            return lista;
        }
        else
        {
            (lista->lanterna)->prox = atual->prox;
            free(atual);
            return expulsa_nao_vacinados((lista->lanterna)->prox, lista);
        }
    }
}
p_lista adiciona_final_fila(p_lista lista, p_no novo)
{
    /* Adiciona nova pessoa no início fim da lista */

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
        lista->fim = novo;
        novo->prox = NULL;
        lista->lanterna = novo;
    }
    else
    {
        novo->prox = NULL;
        (lista->fim)->prox = novo;
        lista->fim = novo;
        lista->lanterna = novo;
    }
    return lista;
}
p_lista adiciona_atras_lanterna(p_lista lista, p_no novo)
{
    /* Adiciona uma nova pessoa atrás da pessoa com a lanterna.
    Casos de exceção: a lanterna estar sendo segurada por um fiscal e a pessoa não estar vacinada. Nesse caso, não será adicionada
    Além disso, caso a pessoa seja um fiscal, todas as pessoas continuamente atrás dela não vacinadas, até que se chegue ao fim da
    lista ou até encontrar uma pessoa vacinada, serão removidas da lista.
    */
    
    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
        lista->fim = novo;
        novo->prox = NULL;
        lista->lanterna = novo;
    }
    else
    {
        if (strcmp((lista->lanterna)->profissao, "fiscal") == 0 && strcmp(novo->status_vacinacao, "nao-vacinado") == 0)
        {   free(novo);
            return lista;
        }
        else
        {   if (lista->lanterna == lista->fim){
                return adiciona_final_fila(lista, novo);
            }
            novo->prox = (lista->lanterna)->prox;
            (lista->lanterna)->prox = novo;
            lista->lanterna = novo;

            if (strcmp(novo->profissao, "fiscal") == 0)
            {
                lista = expulsa_nao_vacinados(novo->prox, lista);
            }
        }
    }

    return lista;
}
p_lista adiciona_inicio_fila(p_lista lista, p_no novo)
{
    /*Adiciona uma pessoa no início da lista */

    if (lista->inicio == NULL)
    {
        lista->inicio = novo;
        lista->fim = novo;
        novo->prox = NULL;
        lista->lanterna = novo;
    }
    else
    {
        novo->prox = lista->inicio;
        lista->inicio = novo;
        lista->lanterna = novo;
    }

    return lista;
}

p_no cria_no(int documento, char *profissao, char *status_vacinacao)
{
    /* Aloca dinamicamente e retorna um p_no, representando uma pessoa, contendo os dados de documento, profissao e status de vacinacao */
    p_no novo = malloc(sizeof(struct no));
    novo->documento = documento;
    strcpy(novo->profissao, profissao);
    strcpy(novo->status_vacinacao, status_vacinacao);

    return novo;
}
void destruir_lista(p_no lista)
{   /* Destroi toda a lista e libera o seu espaço */
    if (lista != NULL)
    {
        destruir_lista(lista->prox);
        free(lista);
    }
}
void imprime_lista(p_no lista)
{   
    /* Imprime uma lista ligada, do primeiro ao último nó, com os dados de documento, profissao e status de vacinacao, um por linha*/

    if (lista != NULL)
    {
        printf("%d %s %s\n", lista->documento, lista->profissao, lista->status_vacinacao);
        imprime_lista(lista->prox);
    }
}

int main()
{
    int documento;
    char profissao[MAX], status_vacinacao[13];
    p_lista lista = cria_nova_lista();

    while (scanf("%d %s %s", &documento, profissao, status_vacinacao) != EOF)
    {
        p_no novo = cria_no(documento, profissao, status_vacinacao);

        if (eh_grupo_prioritario(profissao))
        {
            lista = adiciona_inicio_fila(lista, novo);
        }
        else if (strcmp("funcionario", profissao) == 0)
        {
            lista = adiciona_final_fila(lista, novo);
        }
        else
        {
            lista = adiciona_atras_lanterna(lista, novo);
        }
    }

    imprime_lista(lista->inicio);
    destruir_lista(lista->inicio);
    free(lista);

    return 0;
}
