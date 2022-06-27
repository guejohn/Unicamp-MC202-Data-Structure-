#include <stdio.h>
#include "dns.h"

int main()
{
    int max_consultas_usuario, num_dominios, num_consultas;
    p_nod raiz_d = NULL;
    p_nou raiz_u = NULL;

    scanf("%d\n%d", &max_consultas_usuario, &num_dominios);
    raiz_d = recebe_dominios(num_dominios, raiz_d);

    scanf("%d", &num_consultas);
    raiz_u = realiza_consultas(num_consultas, max_consultas_usuario, raiz_d, raiz_u);

    destroi_arvore_dominios(raiz_d);
    destroi_arvore_usuarios(raiz_u);

    return 0;
}
