#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rpg.h"

int **cria_matriz_adjacente(int n)
{
    /*Cria e aloca dinamicamente uma matriz adjacente de ordem n e retorna o seu endereço */

    int **matriz_adj = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
    {
        matriz_adj[i] = malloc(n * sizeof(int));
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matriz_adj[i][j] = 0;
        }
    }
    return matriz_adj;
}

p_grafo criar_grafo(int num_vertices)
{   
    /*Cria e aloca um novo grafo dinamicamente e retorna o seu endereço */

    p_grafo novo_grafo = malloc(sizeof(struct grafo));
    novo_grafo->matriz_adj = cria_matriz_adjacente(num_vertices);
    novo_grafo->num_vertices = num_vertices;
    novo_grafo->celas = NULL;
    novo_grafo->atributos_iniciais_jogadores = NULL;

    return novo_grafo;
}
p_cela cria_celas(int num_celas)
{
    /* Cria e aloca dinamicamente um vetor representando as celas e retorna o seu endereço */
    p_cela celas = malloc(num_celas * sizeof(struct cela));
    return celas;
}

int **cria_atributos_jogadores(int num_jogadores)
{
    /* Cria e aloca dinamicamente uma matriz (num_jogadores x 6) que representa os atributos (Força, Destreza, Constituição, Inteligência, Sabedoria e Carisma) de cada jogador e retorna o seu endereço */

    int **atributos = malloc(num_jogadores * sizeof(int *));
    for (int i = 0; i < num_jogadores; i++)
    {
        atributos[i] = malloc(6 * sizeof(int));
    }
    return atributos;
}
void recebe_celas(p_grafo grafo, int num_celas)
{
    /* Recebe os dados de nome e atributos de cada cela e armazena no vetor de celas */

    grafo->celas = cria_celas(num_celas);

    for (int i = 0; i < num_celas; i++)
    {
        scanf("%s", grafo->celas[i].nome);
        for (int j = 0; j < 6; j++)
        {
            scanf("%d", &grafo->celas[i].atributos[j]);
        }
    }
}

void recebe_jogadores(p_grafo grafo, int num_jogadores)
{
    /* Recebe os dados dos atributos da cela inicial de cada jogador e armazena no vetor de 'atributos_iniciais_jogadores' */

    grafo->atributos_iniciais_jogadores = cria_atributos_jogadores(num_jogadores);
    for (int i = 0; i < num_jogadores; i++)
    {
        scanf("%*s");
        for (int j = 0; j < 6; j++)
        {
            scanf("%d", &(grafo->atributos_iniciais_jogadores[i][j]));
        }
    }
}

int atributos_iguais(int *atributos1, int *atributos2)
{
    /* Verifica se 'atributos1' e 'atributos2' são iguais. Retorna 1 se sim, 0 se não */

    for (int i = 0; i < 6; i++)
    {
        if (atributos1[i] != atributos2[i])
        {
            return 0;
        }
    }
    return 1;
}
int indice_atributo_cela(p_grafo grafo, int *atributos)
{
    /* Retorna o indice dos atributos da cela no vetor de celas */

    for (int i = 0; i < grafo->num_vertices; i++)
    {
        if (atributos_iguais(grafo->celas[i].atributos, atributos))
        {
            return i;
        }
    }
    return -1;
}

int cumpre_atributos_cela(int *atributos_cela, int *atributos)
{
    /* Verifica se os atributos do jogador cumprem os requisitos da cela, isto é,
    se todos os atributos do jogador são iguais ou maiores do que os atributos da cela. Retorna 1 se sim,
    0 se não */

    for (int i = 0; i < 6; i++)
    {
        if (atributos[i] < atributos_cela[i])
        {
            return 0;
        }
    }
    return 1;
}
void gera_combinacoes(p_grafo grafo, int indice_original, int *atributos, int num_rodada)
{
    /*Como, a cada rodada, o jogador tem a possibilidade de incrementar um atributos em 1,
    gera-se todas as possibilidades de celas que cada jogador pode se transportar em até 2 rodadas,
    criando uma relação no grafo entre o código da cela inicial do jogador e o código da cela final.*/

    if (num_rodada == 2)
    {
        for (int i = 0; i < grafo->num_vertices; i++)
        {
            if (cumpre_atributos_cela(grafo->celas[i].atributos, atributos))
            {
                grafo->matriz_adj[indice_original][indice_atributo_cela(grafo, grafo->celas[i].atributos)] = 1;
            }
        }
    }
    else
    {
        num_rodada += 1;
        for (int i = 0; i < 6; i++)
        {
            atributos[i] += 1;
            gera_combinacoes(grafo, indice_original, atributos, num_rodada);
            atributos[i] -= 1;
        }
    }
}

void verifica_possiveis_celas(p_grafo grafo, int num_jogadores)
{
    /* Gera as possibilidades de cela que cada jogador pode se transportar em até 2 rodadas */

    for (int i = 0; i < num_jogadores; i++)
    {
        gera_combinacoes(grafo, indice_atributo_cela(grafo, grafo->atributos_iniciais_jogadores[i]), grafo->atributos_iniciais_jogadores[i], 0);
    }
}

void imprime_celas_compativeis(p_grafo grafo, int num_jogadores)
{
    /*Imprime os nomes de todas as celas, em ordem, onde todo o grupo de jogadores poderá se encontrar após duas rodadas*/

    int satisfaz_todos_jogadores;
    int celas_encontradas = 0;

    for (int j = 0; j < grafo->num_vertices; j++)
    {
        satisfaz_todos_jogadores = 1;
        for (int i = 0; i < num_jogadores; i++)
        {
            if (grafo->matriz_adj[indice_atributo_cela(grafo, grafo->atributos_iniciais_jogadores[i])][j] == 0)
            {
                satisfaz_todos_jogadores = 0;
                break;
            }
        }
        if (satisfaz_todos_jogadores)
        {
            printf("%s\n", grafo->celas[j].nome);
            celas_encontradas += 1;
        }
    }
    if (!celas_encontradas)
    {
        printf("Impossivel terminar em duas rodadas.\n");
    }
}
void destroi_grafo(p_grafo grafo, int num_jogadores)
{
    /*Destroi o grafo, liberando o espaço de tudo o que o compõe, como a matriz adjacente,
    as celas e os atributos das celas iniciais dos jogadores */

    for (int i = 0; i < grafo->num_vertices; i++)
    {
        free(grafo->matriz_adj[i]);
    }

    for (int i = 0; i < num_jogadores; i++)
    {
        free(grafo->atributos_iniciais_jogadores[i]);
    }
    free(grafo->matriz_adj);
    free(grafo->celas);
    free(grafo->atributos_iniciais_jogadores);
    free(grafo);
}