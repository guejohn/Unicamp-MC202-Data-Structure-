#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "roteador.h"

p_fp cria_fila_prioridade(int capacidade)
{
    /* Cria uma fila de prioridade e retorna o seu endereço */

    p_fp fila = malloc(sizeof(struct fila_prioridade));
    fila->v = malloc(capacidade * sizeof(struct pacote));
    fila->tamanho = 0;
    fila->capacidade = capacidade;
    return fila;
}
p_pacote cria_pacote(int id, int prioridade, int incremento)
{
    /* Cria um pacote, contendo seu id, prioridade e incremento, e retorna o seu endereço */
    p_pacote novo_pacote = malloc(sizeof(struct pacote));
    novo_pacote->id = id;
    novo_pacote->prioridade = prioridade;
    novo_pacote->incremento = incremento;

    return novo_pacote;
}
void troca_pacotes(pacote* pacote1, pacote* pacote2)
{
    /* Troca os pacotes de posição, isto é, coloca o pacote que estava no endereço de 'pacote1' no endereço do 'pacote2' e o
    pacote que estava no endereço do 'pacote2' no endereço do 'pacote1' */

    pacote aux = *pacote1;
    *pacote1 = *pacote2;
    *pacote2 = aux;
}
void sobe_pacote_fila(p_fp fila, int indice_pacote)
{
    /* Sobe o pacote na fila de prioridades quando está em um posição incorreta, isto é, quando está abaixo de pacotes
    com menor prioridade do que a sua, até que atinja a posição correta*/

    if (indice_pacote > 0 && fila->v[pai(indice_pacote)].prioridade < fila->v[indice_pacote].prioridade)
    {
        troca_pacotes(&fila->v[indice_pacote], &fila->v[pai(indice_pacote)]);
        sobe_pacote_fila(fila, pai(indice_pacote));
    }
}
void desce_pacote_fila(p_fp fila, int indice_pacote)
{
    /* Desce o pacote na fila de prioridades quando está em um posição incorreta, isto é, quando está acima de pacotes
    com maior prioridade do que a sua, até que atinja a posição correta*/

    int maior_filho;
    if (filho_esq(indice_pacote) < fila->tamanho)
    {
        maior_filho = filho_esq(indice_pacote);
        if (filho_dir(indice_pacote) < fila->tamanho && fila->v[filho_esq(indice_pacote)].prioridade < fila->v[filho_dir(indice_pacote)].prioridade)
            maior_filho = filho_dir(indice_pacote);
        if (fila->v[indice_pacote].prioridade < fila->v[maior_filho].prioridade)
        {
            troca_pacotes(&fila->v[indice_pacote], &fila->v[maior_filho]);
            desce_pacote_fila(fila, maior_filho);
        }
    }
}
void insere_fila(p_fp fila, pacote pacote)
{
    /*Insere 'pacote' na fila e reorganiza a sua posição até que não fique abaixo de nenhum pacote com menor prioridade
    que a sua */

    fila->v[fila->tamanho] = pacote;
    fila->tamanho++;
    sobe_pacote_fila(fila, fila->tamanho - 1);
}

pacote extrai_maximo(p_fp fila)
{
    /* Extrai o pacote de maior prioridade da fila de prioridades, retornando o pacote. Troca o primeiro elemento
    com o último, decrementa 1 do tamanho da lista e reorganiza a fila de forma com que o pacote agora em primeira posição não 
    fique acima de algum pacote com maior prioridade que a sua, respeitando a estrutura de max-heap. */

    pacote pacote = fila->v[0];
    troca_pacotes(&fila->v[0], &fila->v[fila->tamanho - 1]);
    fila->tamanho--;
    desce_pacote_fila(fila, 0);
    return pacote;
}

void emite_tick(p_fp fila, int max_pacotes_enviar, int num_ticket)
{

    /* Emite um tick, imprimindo os dados de id, prioridade e incremento dos pacotes liberados - sendo o máximo o
    'max_pacotes_enviar' - e os extraindo da lista */

    int pacotes_enviar = max_pacotes_enviar;
    pacote elemento_extraido;

    if (fila->tamanho < max_pacotes_enviar)
    {
        pacotes_enviar = fila->tamanho;
    }

    printf("TICK %d\n", num_ticket);

    for (int i = 0; i < pacotes_enviar; i++)
    {
        elemento_extraido = extrai_maximo(fila);
        printf("%d %d %d\n", elemento_extraido.id, elemento_extraido.prioridade, elemento_extraido.incremento);
    }
    printf("\n");
}
void atualiza_prioridade(p_fp fila)
{

    /* Atualiza a prioridade dos pacotes remanescentes da fila para a prioridade atual do pacote + o incremento do pacote */

    for (int i = 0; i < fila->tamanho; i++)
    {
        fila->v[i].prioridade += fila->v[i].incremento;
        sobe_pacote_fila(fila, i);
    }
}
void recebe_informacoes(p_fp fila, int capacidade_fila, int max_pacotes_enviar)
{

    /* Recebe os dados dos pacotes, os insere na fila de prioridade e emite um tick quando os dados forem
    iguais a '0 0 0', atualizando as prioridades dos pacotes remanescentes para a prioridade atual do pacote + o incremento do
    pacote. */

    int id, prioridade, incremento, ticket_atual = 0;

    while (scanf("%d %d %d", &id, &prioridade, &incremento) != EOF)
    {
        if (id == 0 && prioridade == 0 && incremento == 0)
        {
            ticket_atual += 1;
            emite_tick(fila, max_pacotes_enviar, ticket_atual);
            atualiza_prioridade(fila);
        }
        else
        {
            if (fila->tamanho != fila->capacidade)
            {
                p_pacote novo_pacote = cria_pacote(id, prioridade, incremento);
                insere_fila(fila, *novo_pacote);
                free(novo_pacote);
            }
        }
    }
}

void destroi_fila(p_fp fila)
{
    /* Destroi a fila de prioridades, liberando o espaço que foi alocado dinamicamente */

    free(fila->v);
    free(fila);
}