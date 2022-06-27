#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "docas.h"

p_container cria_container(char *mercadoria)
{
    /*Cria um novo container alocado dinacamente, com mercadoria igual a 'mercadoria' e retorna seu endereço */
    p_container novo_container = malloc(sizeof(struct container));
    strcpy(novo_container->mercadoria, mercadoria);
    return novo_container;
}

void empilha_container(p_doca doca, p_container container)
{
    /*Empilha, ou seja, insere o 'container' no TOPO da 'doca' */
    container->prox = doca->container_topo;
    doca->container_topo = container;
}

void desempilha_container(p_doca doca)
{
    /*Desempilha, ou seja, remove o container do TOPO da 'doca' */
    p_container aux_prox = doca->container_topo->prox;
    free(doca->container_topo);
    doca->container_topo = aux_prox;
}

void carrega_navio(p_navio navio, p_doca doca)
{
    /*Carrega o navio com os containers de mesma mercadoria do navio, de acordo com a quantidade disponível dessa mercadoria
    na doca e exibe a operação no formato:
    "{nome do navio} carrega {mercadoria} doca: {numero da doca} conteineres: {numero de containers carregados}" */

    p_navio navio_atual = navio;
    int cont = 0;

    while (1)
    {
        desempilha_container(doca);
        doca->num_containers -= 1;
        navio_atual->quantidade_restante -= 1;
        cont += 1;
        if (doca->container_topo == NULL || strcmp(doca->container_topo->mercadoria, navio->mercadoria) != 0 || navio_atual->quantidade_restante == 0)
        {
            break;
        }
    }
    printf("%s %s %s doca: %d conteineres: %d\n", navio_atual->nome, navio_atual->operacao, navio_atual->mercadoria, doca->num, cont);
}
void descarrega_navio(p_navio navio_atual, p_doca doca, int capacidade_doca)
{
    /*Descarrega os containers do 'navio_atual' na 'doca', de acordo com a 'capacidade_doca' e
    exibe a operação no formato:
    "{nome do navio} descarrega {mercadoria} doca: {numero da doca} conteineres: {numero de containers descarregados}" */

    p_container novo_container;

    if (navio_atual->quantidade_restante <= (capacidade_doca - doca->num_containers))
    {
        for (int i = 0; i < navio_atual->quantidade_restante; i++)
        {
            novo_container = cria_container(navio_atual->mercadoria);
            empilha_container(doca, novo_container);
        }
        printf("%s %s %s doca: %d conteineres: %d\n", navio_atual->nome, navio_atual->operacao, navio_atual->mercadoria, doca->num, navio_atual->quantidade_restante);
        doca->num_containers += navio_atual->quantidade_restante;
        navio_atual->quantidade_restante = 0;
    }
    else
    {
        for (int i = 0; i < (capacidade_doca - doca->num_containers); i++)
        {
            novo_container = cria_container(navio_atual->mercadoria);
            empilha_container(doca, novo_container);
        }
        printf("%s %s %s doca: %d conteineres: %d\n", navio_atual->nome, navio_atual->operacao, navio_atual->mercadoria, doca->num, capacidade_doca - doca->num_containers);
        navio_atual->quantidade_restante -= (capacidade_doca - doca->num_containers);
        doca->num_containers = capacidade_doca;
    }
}
p_doca encontra_doca_disponivel(p_doca *vetor_docas, char *operacao, char *mercadoria, int capacidade_doca, int num_docas)
{
    /*Encontra uma doca disponível que satisfaça a condição da 'operacao' do navio. Quando a operacao é igual a 'carregar',
    retorna o endereço da primeira doca com a mercadoria do container do topo da doca igual a 'mercadoria'. Quando é igual
    a 'descarregar', retorna o endereço da primeira doca com, pelo menos, o espaço de um container disponível.
    Quando não existe a doca necessária, retorna NULL */

    p_doca doca_atual;

    if (strcmp(operacao, "carrega") == 0)
    {
        for (int i = 0; i < num_docas; i++)
        {
            doca_atual = vetor_docas[i];
            if (doca_atual->container_topo != NULL)
            {
                if (strcmp(doca_atual->container_topo->mercadoria, mercadoria) == 0)
                {
                    return doca_atual;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < num_docas; i++)
        {
            doca_atual = vetor_docas[i];
            if (doca_atual->num_containers < capacidade_doca)
            {
                return doca_atual;
            }
        }
    }
    return NULL;
}
void navio_fim_fila(p_fila fila)
{
    /*Remaneja o navio do INÍCIO para o FIM da fila*/

    fila->fim->prox = fila->ini;
    fila->fim = fila->ini;
    fila->ini = fila->fim->prox;
    fila->fim->prox = NULL;
}
void desenfileira_navio(p_fila fila)
{
    /*Desenfileira, ou seja, remove o navio do INÍCIO da lista*/

    p_navio aux_proximo;

    if (fila->ini != NULL)
    {
        if (fila->ini != fila->fim)
        {
            aux_proximo = fila->ini->prox;
            free(fila->ini);
            fila->ini = aux_proximo;
        }
        else
        {
            free(fila->ini);
            fila->ini = NULL;
            fila->fim = NULL;
        }
    }
}
p_fila cria_fila()
{
    /*Cria uma fila alocada dinamicamente, com inicio e fim iguais a NULL, e retorna seu endereço */

    p_fila nova_fila = malloc(sizeof(struct fila));
    nova_fila->ini = NULL;
    nova_fila->fim = NULL;
    return nova_fila;
}
void enfileira_navio(p_fila fila, p_navio navio)
{
    /*Enfileira 'navio' na 'fila', isto é, adiciona 'navio' ao FIM da fila*/

    if (fila->ini == NULL)
    {
        fila->ini = navio;
        fila->fim = navio;
    }
    else
    {
        navio->prox = NULL;
        fila->fim->prox = navio;
        fila->fim = navio;
    }
}
p_navio cria_navio()
{
    /*Cria um navio alocado dinamicamente e retorna o seu endereço */

    p_navio novo_navio = malloc(sizeof(struct navio));
    return novo_navio;
}

void destroi_fila_navios(p_fila fila)
{
    /* Libera o espaço que foi dinamicamente alocado para uma 'fila' de navios,
    incluindo todos os seus nós */

    p_navio atual = fila->ini, aux_proximo;

    if (fila->ini != NULL && fila->fim != NULL)
    {
        while (1)
        {
            if (atual == fila->fim)
            {
                free(atual);
                break;
            }
            else
            {
                aux_proximo = atual->prox;
                free(atual);
                atual = aux_proximo;
            }
        }
    }
    free(fila);
}

void gerencia_fluxo(p_fila fila, p_doca *vetor_docas, int capacidade_doca, int num_docas, int num_navios)
{
    /*Gerencia o fluxo do porto, descarregando e carregando os navios. Quando um navio cumpre o seu propósito,
    ele é desenfileirado da fila de navios. Se não for possível esvaziar a fila depois de todas operações de carga e descarga,
    é exibida uma mensagem: "ALERTA: impossivel esvaziar fila, restam N navios.", onde "N" é o número de navios ainda presentes
    na fila */

    p_navio navio_atual;
    p_doca doca_disponivel;
    int containers_remanescentes, num_pendencias = 0;

    while (fila->ini != NULL)
    {
        navio_atual = fila->ini;
        doca_disponivel = encontra_doca_disponivel(vetor_docas, navio_atual->operacao, navio_atual->mercadoria, capacidade_doca, num_docas);

        if (doca_disponivel != NULL)
        {
            if (strcmp(navio_atual->operacao, "descarrega") == 0)
            {
                descarrega_navio(navio_atual, doca_disponivel, capacidade_doca);
            }
            else
            {
                carrega_navio(navio_atual, doca_disponivel);
            }

            containers_remanescentes = navio_atual->quantidade_restante;

            if (containers_remanescentes > 0)
            {
                navio_fim_fila(fila);
            }
            else
            {
                desenfileira_navio(fila);
                num_navios -= 1;
            }
            num_pendencias = 0;
        }
        else
        {
            num_pendencias += 1;
            if (num_navios == num_pendencias)
            {
                printf("ALERTA: impossivel esvaziar fila, restam %d navios.\n", num_pendencias);
                break;
            }
            navio_fim_fila(fila);
        }
    }
}
p_doca *cria_docas(int num_docas)
{
    /* Cria um vetor alocado dinamicamente com 'num_docas' posicoes, inicializa seus parâmetros
    e retorna o ponteiro da primeira posicao */

    p_doca *vetor_docas;

    vetor_docas = malloc(num_docas * sizeof(p_doca *));
    for (int i = 0; i < num_docas; i++)
    {
        vetor_docas[i] = malloc(sizeof(struct doca));
        vetor_docas[i]->container_topo = NULL;
        vetor_docas[i]->num = i;
        vetor_docas[i]->num_containers = 0;
    }
    return vetor_docas;
}

void recebe_navios(p_fila fila_navios, int num_navios)
{
    /*Lê os 'num_navios' navios, criando-os de acordo com os dados lidos, e os enfileira na 'fila_navios' */

    p_navio novo_navio;

    for (int i = 0; i < num_navios; i++)
    {

        novo_navio = cria_navio();
        scanf("%s %s %s %d", novo_navio->nome, novo_navio->operacao, novo_navio->mercadoria, &novo_navio->quantidade_restante);
        enfileira_navio(fila_navios, novo_navio);
    }
}

void le_dados(int *num_docas, int *capacidade_doca, int *num_navios)
{
    /*Lê os dados do número de docas do porto, a capacidade de containers de cada doca e o número de navios e os
    armazena em suas respectivas variáveis */
    scanf("%d", num_docas);
    scanf("%d", capacidade_doca);
    scanf("%d", num_navios);
}
void destroi_docas(p_doca *vetor_docas, int num_docas)
{
    /*Libera o espaço alocado dinamicamente para as docas*/

    for (int i = 0; i < num_docas; i++)
    {
        free(vetor_docas[i]);
    }
    free(vetor_docas);
}