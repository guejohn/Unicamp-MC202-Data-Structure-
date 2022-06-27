#include <stdio.h>
#include "rpg.h"

int main()
{
    int num_celas, num_jogadores;

    scanf("%d", &num_celas);

    p_grafo grafo = criar_grafo(num_celas);
    recebe_celas(grafo, num_celas);

    scanf("%d", &num_jogadores);
    recebe_jogadores(grafo, num_jogadores);

    verifica_possiveis_celas(grafo, num_jogadores);
    imprime_celas_compativeis(grafo, num_jogadores);

    destroi_grafo(grafo, num_jogadores);
    return 0;
}
