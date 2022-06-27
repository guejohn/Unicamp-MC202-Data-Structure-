#include <stdio.h>
#include <stdlib.h>

typedef struct no *p_no;
typedef struct lista *p_lista;

struct no
{
    int altura;
    p_no ant;
    p_no prox;
};

struct lista
{
    p_no ini;
    p_no fim;
};

void destruir_lista(p_lista lista)
{
    /* Libera o espaço que foi dinamicamente alocado para a 'lista',
    incluindo todos os seus nós */

    p_no atual = lista->ini, aux_proximo;

    if (lista->ini != NULL && lista->fim != NULL)
    {
        while (1)
        {
            if (atual == lista->fim)
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
    free(lista);
}

void imprime_lista(p_lista lista)
{
    /* Imprime todos os elementos de uma lista circular, um por vez e separados por espaço,
    de 'lista'->ini até 'lista'->fim */

    p_no atual = lista->ini;

    do
    {
        printf("%d ", atual->altura);
        atual = atual->prox;
    } while (atual != lista->ini);
    printf("\n");
}

p_lista cria_lista()
{
    /*Aloca dinamicamente o espaço para uma nova lista e retorna o seu endereço */

    p_lista nova_lista = malloc(sizeof(struct lista));
    nova_lista->ini = NULL;
    nova_lista->fim = NULL;

    return nova_lista;
}

p_no cria_jogador(int altura)
{
    /*Cria um novo jogador de altura 'altura', representado por um nó alocado dinamicamente, e o retorna */

    p_no novo_jogador = malloc(sizeof(struct no));
    novo_jogador->altura = altura;
    novo_jogador->ant = NULL;
    novo_jogador->prox = NULL;

    return novo_jogador;
}

void adiciona_jogador(p_no jogador, p_lista lista)
{
    /*Adiciona um novo jogador, ou seja, um nó, ao fim de uma lista circular*/

    if (lista->ini == NULL)
    {
        jogador->prox = jogador;
        jogador->ant = jogador;
        lista->ini = jogador;
        lista->fim = jogador;
    }
    else
    {
        jogador->prox = lista->ini;
        jogador->ant = lista->fim;
        (lista->fim)->prox = jogador;
        (lista->ini)->ant = jogador;
        lista->fim = jogador;
    }
}

void recebe_jogadores(int num_jogadores, p_lista lista)
{
    /* Lê sequencialmente as alturas da entrada do teclado,
    cria novos jogadores com essas alturas e os adiciona à 'lista' */

    int altura;
    for (int i = 0; i < num_jogadores; i++)
    {
        scanf("%d ", &altura);
        p_no jogador = cria_jogador(altura);
        adiciona_jogador(jogador, lista);
    }
}

p_no percorre_posicoes(p_no posicao_atual, int num_posicoes, int contador)
{
    /* Percorre 'num_posicoes' desde a 'posicao_atual' e retorna o jogador da posição encontrada */

    for (int i = 0; i < num_posicoes; i++)
    {
        if (contador % 2 == 0)
        {
            posicao_atual = posicao_atual->prox;
        }
        else
        {
            posicao_atual = posicao_atual->ant;
        }
    }
    return posicao_atual;
}

p_lista retira_jogador(p_no jogador, p_lista lista)
{
    /* Retira o 'jogador' de uma lista e libera o espaço ocupado por ele */

    if (jogador == lista->ini && jogador == lista->fim)
    {
        lista->ini = NULL;
        lista->fim = NULL;
    }
    else if (jogador == lista->ini)
    {
        (lista->fim)->prox = (lista->ini)->prox;
        (lista->ini->prox)->ant = lista->fim;
        lista->ini = lista->ini->prox;
    }
    else if (jogador == lista->fim)
    {
        (jogador->ant)->prox = lista->ini;
        (lista->ini)->ant = jogador->ant;
        lista->fim = jogador->ant;
    }
    else
    {
        (jogador->ant)->prox = jogador->prox;
        (jogador->prox)->ant = jogador->ant;
    }

    free(jogador);
    return lista;
}

int lista_ordenada(p_lista lista)
{
    /* Verifica se uma lista está ordenada. Se estiver, retorna 1. Do contrário, retorna 0 */

    p_no atual = lista->ini;
    do
    {
        if (atual->altura > (atual->prox)->altura)
        {
            return 0;
        }
        atual = atual->prox;
    } while (atual->prox != lista->ini);

    return 1;
}

p_lista ordena_lista(p_lista lista)
{
    /* Ordena crescentemente os nós de uma lista, de acordo com as ALTURAS dos jogadores */

    p_no atual = lista->ini, aux_proximo;
    p_no copia_jogador_atual;

    if (lista_ordenada(lista))
    {
        return lista;
    }
    do
    {
        aux_proximo = atual->prox;
        if (atual->altura > atual->prox->altura)
        {
            copia_jogador_atual = cria_jogador(atual->altura);
            lista = retira_jogador(atual, lista);
            adiciona_jogador(copia_jogador_atual, lista);
        }
        atual = aux_proximo;
    } while (atual != lista->ini);

    return ordena_lista(lista);
}

void sorteia_times(p_lista lista, p_lista time1, p_lista time2, int num_jogadores)
{
    /*Lê os valores sorteados do teclado e, para cada valor, percorre (valor sorteado - 1) posições da lista, retira o jogador
    da 'lista' e o coloca no 'time1' ou 'time2'. 
    Começando na rodada 1, se a rodada é ímpar, se percorre as posições no sentido anti-horário e se insere o jogador no time1.
    Se a rodada é par, se percorre as posições no sentido horário e se insere o jogador no time2 */

    int valor_sorteado, contador = 1;
    p_no jogador_sorteado;

    for (int i = 0; i < num_jogadores; i++)
    {
        scanf("%d", &valor_sorteado);
        jogador_sorteado = percorre_posicoes(lista->ini, valor_sorteado - 1, contador);
        p_no novo_jogador = cria_jogador(jogador_sorteado->altura);
        if (contador % 2 != 0)
        {
            adiciona_jogador(novo_jogador, time1);
        }
        else
        {
            adiciona_jogador(novo_jogador, time2);
        }
        lista = retira_jogador(jogador_sorteado, lista);
        contador += 1;
    }
}
int main()
{
    int num_jogadores;

    //criando as listas
    p_lista lista = cria_lista();
    p_lista time1 = cria_lista();
    p_lista time2 = cria_lista();

    //recebendo os jogadores
    scanf("%d", &num_jogadores);
    recebe_jogadores(num_jogadores, lista);

    //sorteando os times
    sorteia_times(lista, time1, time2, num_jogadores);

    //ordenando os times
    time1 = ordena_lista(time1);
    time2 = ordena_lista(time2);

    //imprimindo os times
    imprime_lista(time1);
    imprime_lista(time2);

    //destruindo as listas
    destruir_lista(time1);
    destruir_lista(time2);
    destruir_lista(lista);
    
    return 0;
}
