#include <stdio.h>
#include "roteador.h"

int main()
{
    int max_pacotes_enviar, capacidade_fila;
    scanf("%d %d", &max_pacotes_enviar, &capacidade_fila);

    p_fp fila = cria_fila_prioridade(capacidade_fila);
    recebe_informacoes(fila, capacidade_fila, max_pacotes_enviar);

    destroi_fila(fila);
    return 0;
}
