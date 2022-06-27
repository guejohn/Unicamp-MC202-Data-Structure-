#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dns.h"

p_nod cria_no_dominio(char *dominio, char *servidor_DNS)
{
    /* Cria e aloca dinamicamente um novo nó de domínio e retorna o seu endereço */

    p_nod novo_nod = malloc(sizeof(struct no_dominio));

    strcpy(novo_nod->dominio, dominio);
    strcpy(novo_nod->servidor_DNS, servidor_DNS);
    novo_nod->cor = VERMELHO;
    novo_nod->esq = NULL;
    novo_nod->dir = NULL;

    return novo_nod;
}

p_nou cria_no_usuario(char *ip)
{
    /* Cria e aloca dinamicamente um novo nó de usuário e retorna o seu endereço */

    p_nou novo_nou = malloc(sizeof(struct no_usuario));

    strcpy(novo_nou->ip, ip);
    novo_nou->cor = VERMELHO;
    novo_nou->num_consultas = 0;
    novo_nou->esq = NULL;
    novo_nou->dir = NULL;

    return novo_nou;
}

p_nod busca_no_dominio(p_nod raiz, char *dominio)
{
    /* Busca o nó_dominio de domínio igual a 'domínio' na árvore binária de busca de domínios, e retorna o seu endereço.
    Se o domínio não existir na árvore, retornará NULL */

    while (raiz != NULL && strcmp(dominio, raiz->dominio) != 0)
        if (strcmp(dominio, raiz->dominio) < 0)
        {
            raiz = raiz->esq;
        }
        else
        {
            raiz = raiz->dir;
        }
    return raiz;
}

p_nou busca_no_usuario(p_nou raiz, char *ip)
{
    /* Busca o nó_usuário de ip igual a 'ip' na árvore binária de busca de usuários, e retorna o seu endereço.
    Se o ip não existir na árvore, retornará NULL */

    while (raiz != NULL && strcmp(ip, raiz->ip) != 0)
        if (strcmp(ip, raiz->ip) < 0)
        {
            raiz = raiz->esq;
        }
        else
        {
            raiz = raiz->dir;
        }
    return raiz;
}

int ehVermelho_d(p_nod no_d)
{
    /* Verifica se a cor do nó de DOMÍNIO é vermelha. Se o nó for nulo, tem-se por convenção de árvore rubro-negra que sua cor
    deve ser preta e, portanto, retorna 0. Do contrário, se o nó não for nulo, retorna 1 se a cor for vermelha e 0 se não for. */

    if (no_d == NULL)
    {
        return 0;
    }
    return no_d->cor == VERMELHO;
}

int ehVermelho_u(p_nou no_u)
{
    /* Verifica se a cor do nó de USUÁRIO é vermelha. Se o nó for nulo, tem-se por convenção de árvore rubro-negra que sua cor
    deve ser preta e, portanto, retorna 0. Do contrário, se o nó não for nulo, retorna 1, se a cor for vermelha, e 0, se não for. */

    if (no_u == NULL)
    {
        return 0;
    }
    return no_u->cor == VERMELHO;
}

int ehPreto_d(p_nod no_d)
{
    /* Verifica se a cor do nó de DOMÍNIO é preta. Se o nó for nulo, tem-se por convenção de árvore rubro-negra que sua cor deve ser
    preta e, portanto, retorna 1. Do contrário, se o nó não for nulo, retorna 0, se a cor não for preta, e 1, se for. */

    if (no_d == NULL)
    {
        return 1;
    }
    return no_d->cor == PRETO;
}

int ehPreto_u(p_nou no_u)
{
    /* Verifica se a cor do nó de USUÁRIO é preta. Se o nó for nulo, tem-se por convenção de árvore rubro-negra que sua cor
    deve ser preta e, portanto, retorna 1. Do contrário, se o nó não for nulo, retorna 0, se a cor não for preta, e 1, se for. */

    if (no_u == NULL)
    {
        return 1;
    }
    return no_u->cor == PRETO;
}

p_nod rotaciona_para_esquerda_d(p_nod raiz)
{
    /*Rotaciona a árvore de busca binário rubro-negra de DOMÍNIOS - representada por 'raiz' - para a esquerda, isto é, a nova raiz
    é a filha direita da raiz original, a raiz original vira filha esquerda da nova raiz e a filha esquerda da raiz original vira
    filha esquerda da filha esquerda da nova raiz */

    p_nod no_atual = raiz->dir;
    raiz->dir = no_atual->esq;
    no_atual->esq = raiz;
    no_atual->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return no_atual;
}
p_nou rotaciona_para_esquerda_u(p_nou raiz)
{
    /*Rotaciona a árvore de busca binário rubro-negra de USUÁRIOS - representada por 'raiz' - para a esquerda, isto é, a nova raiz
    é a filha direita da raiz original, a raiz original vira filha esquerda da nova raiz e a filha esquerda da raiz original vira
    filha esquerda da filha esquerda da nova raiz */

    p_nou no_atual = raiz->dir;
    raiz->dir = no_atual->esq;
    no_atual->esq = raiz;
    no_atual->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return no_atual;
}

p_nod rotaciona_para_direita_d(p_nod raiz)
{
    /*Rotaciona a árvore de busca binário rubro-negra de DOMÍNIOS - representada por 'raiz' - para a direita, isto é, a nova raiz é
    a filha esquerda da raiz original, a raiz original vira filha direita da nova raiz e a filha direita da raiz original vira filha
    direita da filha direita da nova raiz */

    p_nod no_atual = raiz->esq;
    raiz->esq = no_atual->dir;
    no_atual->dir = raiz;
    no_atual->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return no_atual;
}

p_nou rotaciona_para_direita_u(p_nou raiz)
{
    /*Rotaciona a árvore de busca binário rubro-negra de USUÁRIOS - representada por 'raiz' - para a direita, isto é, a nova raiz é
    a filha esquerda da raiz original, a raiz original vira filha direita da nova raiz e a filha direita da raiz original vira filha
    direita da filha direita da nova raiz */

    p_nou no_atual = raiz->esq;
    raiz->esq = no_atual->dir;
    no_atual->dir = raiz;
    no_atual->cor = raiz->cor;
    raiz->cor = VERMELHO;
    return no_atual;
}
void sobe_vermelho_d(p_nod raiz)
{   
    /* Modifica a cor do nó_dominio 'raiz' para vermelho e a cor de seus dois nós filhos para preto */

    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

void sobe_vermelho_u(p_nou raiz)
{
    /* Modifica a cor do nó_usuario 'raiz' para vermelho e a cor de seus dois nós filhos para preto */

    raiz->cor = VERMELHO;
    raiz->esq->cor = PRETO;
    raiz->dir->cor = PRETO;
}

p_nod insere_dominio(p_nod raiz, char *dominio, char *servidor_DNS)
{
    /*Insere o domínio, representado por um endereço de domínio e um endereço de servidor DNS associado, na árvore binária
    de busca balanceada rubro-negra de domínios, representada por 'raiz', e retorna a raiz da árvore com o novo domínio incluso.*/

    p_nod novo;
    if (raiz == NULL)
    {
        novo = cria_no_dominio(dominio, servidor_DNS);
        return novo;
    }
    else if (strcmp(dominio, raiz->dominio) < 0)
    {
        raiz->esq = insere_dominio(raiz->esq, dominio, servidor_DNS);
    }
    else
    {
        raiz->dir = insere_dominio(raiz->dir, dominio, servidor_DNS);
    }
    if (ehVermelho_d(raiz->dir) && ehPreto_d(raiz->esq))
    {
        raiz = rotaciona_para_esquerda_d(raiz);
    }
    if (ehVermelho_d(raiz->esq) && ehVermelho_d(raiz->esq->esq))
    {
        raiz = rotaciona_para_direita_d(raiz);
    }
    if (ehVermelho_d(raiz->esq) && ehVermelho_d(raiz->dir))
    {
        sobe_vermelho_d(raiz);
    }
    return raiz;
}

p_nou insere_usuario(p_nou raiz, char *ip)
{
    /*Insere o usuário, representado por um endereço IP, na árvore binária de busca balanceada rubro-negra de usuários, 
    representada por 'raiz', e retorna a raiz da árvore com o novo usuário incluso. Se o IP já estiver presente na árvore,
    simplesmente retorna a raiz original */

    if (raiz == NULL)
    {
        p_nou novo = cria_no_usuario(ip);
        return novo;
    }
    else if (strcmp(ip, raiz->ip) == 0)
    {
        return raiz;
    }
    else if (strcmp(ip, raiz->ip) < 0)
    {
        raiz->esq = insere_usuario(raiz->esq, ip);
    }
    else
    {
        raiz->dir = insere_usuario(raiz->dir, ip);
    }
    if (ehVermelho_u(raiz->dir) && ehPreto_u(raiz->esq))
    {
        raiz = rotaciona_para_esquerda_u(raiz);
    }
    if (ehVermelho_u(raiz->esq) && ehVermelho_u(raiz->esq->esq))
    {
        raiz = rotaciona_para_direita_u(raiz);
    }
    if (ehVermelho_u(raiz->esq) && ehVermelho_u(raiz->dir))
    {
        sobe_vermelho_u(raiz);
    }
    return raiz;
}

p_nod recebe_dominios(int num_dominios, p_nod raiz_d)
{
    /*Lê os 'num_dominios' dominios, compostos por um endereço de domínio e por um endereço de um servidor DNS associado. 
    Depois, insere os domínios na árvore binária balanceada rubro-negra de domínios, representada por 'raiz_d' */

    char dominio[101], servidor_DNS[20];

    for (int i = 0; i < num_dominios; i++)
    {
        scanf("%s %s", dominio, servidor_DNS);
        raiz_d = insere_dominio(raiz_d, dominio, servidor_DNS);
    }
    return raiz_d;
}

p_nou realiza_consultas(int num_consultas, int max_consultas_usuario, p_nod raiz_d, p_nou raiz_u)
{
    /*Lê as 'num_consultas', compostas por um domínio e pelo ip do usuário que realiza a consulta e imprime:
    - "NOTFOUND {dominio} FROM {ip_usuario}" se o domínio consultado não existe;
    - "ACCEPTED {dominio} FROM {ip_usuario} RESPOND {servidor_DNS_associado}" se o domínio consultado foi encontrado e o
    usuário não ultrapassou o limite de consultas ('max_consultas_usuario') estabelecido;
    - "FORBIDDEN {dominio} FROM {ip_usuario}" se o usuário ultrapassou o limite de consultas estabelecido. */

    p_nou no_usuario;
    p_nod no_dominio;
    char dominio_consulta[101], ip_usuario[20];

    for (int i = 0; i < num_consultas; i++)
    {
        scanf("%*s %s %*s %s", dominio_consulta, ip_usuario);
        raiz_u = insere_usuario(raiz_u, ip_usuario);
        no_usuario = busca_no_usuario(raiz_u, ip_usuario);
        no_usuario->num_consultas += 1;
        if (no_usuario->num_consultas <= max_consultas_usuario)
        {
            no_dominio = busca_no_dominio(raiz_d, dominio_consulta);
            if (no_dominio == NULL)
            {
                printf("NOTFOUND %s FROM %s\n", dominio_consulta, ip_usuario);
            }
            else
            {
                printf("ACCEPTED %s FROM %s RESPOND %s\n", dominio_consulta, ip_usuario, no_dominio->servidor_DNS);
            }
        }
        else
        {
            printf("FORBIDDEN %s FROM %s\n", dominio_consulta, ip_usuario);
        }
    }
    return raiz_u;
}

void destroi_arvore_dominios(p_nod raiz)
{
    /*Destrói a árvore binária de domínios, liberando o espaço de todos os seus nós.*/

    if (raiz != NULL)
    {
        destroi_arvore_dominios(raiz->dir);
        destroi_arvore_dominios(raiz->esq);
        free(raiz);
    }
}

void destroi_arvore_usuarios(p_nou raiz)
{
    /*Destrói a árvore binária de usuários, liberando o espaço de todos os seus nós.*/

    if (raiz != NULL)
    {
        destroi_arvore_usuarios(raiz->dir);
        destroi_arvore_usuarios(raiz->esq);
        free(raiz);
    }
}