#include "docas.h"

int main()
{
    int num_docas, capacidade_doca, num_navios;
    p_doca *vetor_docas;
    p_fila fila_navios = cria_fila();

    le_dados(&num_docas, &capacidade_doca, &num_navios);
    vetor_docas = cria_docas(num_docas);
    recebe_navios(fila_navios, num_navios);
    gerencia_fluxo(fila_navios, vetor_docas, capacidade_doca, num_docas, num_navios);

    destroi_fila_navios(fila_navios);
    destroi_docas(vetor_docas, num_docas);
    return 0;
}
