#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct grafo *p_grafo;
typedef struct cela *p_cela;

struct grafo
{
    int **matriz_adj;
    p_cela celas;
    int **atributos_iniciais_jogadores;
    int num_vertices;
};
struct cela
{
    char nome[30];
    int atributos[6];
};

/*Cria e aloca dinamicamente uma matriz adjacente de ordem n e retorna o seu endereço */
int **cria_matriz_adjacente(int n);

/*Cria e aloca um novo grafo dinamicamente e retorna o seu endereço */
p_grafo criar_grafo(int num_vertices);

/* Cria e aloca dinamicamente um vetor representando as celas e retorna o seu endereço */
p_cela cria_celas(int num_celas);

/* Cria e aloca dinamicamente uma matriz (num_jogadores x 6) que representa os atributos
(Força, Destreza, Constituição, Inteligência, Sabedoria e Carisma) de cada jogador e retorna o seu endereço */
int **cria_atributos_jogadores(int num_jogadores);

/* Recebe os dados de nome e atributos de cada cela e armazena no vetor de celas */
void recebe_celas(p_grafo grafo, int num_celas);

/* Recebe os dados dos atributos da cela inicial de cada jogador e armazena no vetor de 'atributos_iniciais_jogadores' */
void recebe_jogadores(p_grafo grafo, int num_jogadores);

/* Verifica se 'atributos1' e 'atributos2' são iguais. Retorna 1 se sim, 0 se não */
int atributos_iguais(int *atributos1, int *atributos2);

/* Retorna o indice dos atributos da cela no vetor de celas */
int indice_atributo_cela(p_grafo grafo, int *atributos);

/* Verifica se os atributos do jogador cumprem os requisitos da cela, isto é,
se todos os atributos do jogador são iguais ou maiores do que os atributos da cela. Retorna 1 se sim,
0 se não */
int cumpre_atributos_cela(int *atributos_cela, int *atributos);

/*Como, a cada rodada, o jogador tem a possibilidade de incrementar um atributos em 1,
gera-se todas as possibilidades de celas que cada jogador pode se transportar em até 2 rodadas,
criando uma relação no grafo entre o código da cela inicial do jogador e o código da cela final.*/
void gera_combinacoes(p_grafo grafo, int indice_original, int *atributos, int num_rodada);

/* Gera as possibilidades de cela que cada jogador pode se transportar em até 2 rodadas */
void verifica_possiveis_celas(p_grafo grafo, int num_jogadores);

/*Imprime os nomes de todas as celas, em ordem, onde todo o grupo de jogadores poderá se encontrar após duas rodadas*/
void imprime_celas_compativeis(p_grafo grafo, int num_jogadores);

/*Destroi o grafo, liberando o espaço de tudo o que o compõe, como a matriz adjacente,
as celas e os atributos das celas iniciais dos jogadores */
void destroi_grafo(p_grafo grafo, int num_jogadores);

