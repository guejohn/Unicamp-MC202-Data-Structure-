#include <stdio.h>
#include "busca.h"

int main()
{
    int num_anuncios, num_buscas;
    p_noc raiz_c = NULL;

    scanf("%d", &num_anuncios);
    raiz_c = recebe_anuncios(num_anuncios, raiz_c);

    scanf("%d", &num_buscas);
    busca_ofertas(num_buscas, raiz_c);

    destroi_arvore(raiz_c);
    return 0;
}
