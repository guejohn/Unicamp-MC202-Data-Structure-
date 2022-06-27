#include <stdio.h>
#include "piramide.h"

int main()
{
    char nome_recrutador[21], nome_recrutado[21];
    float valor;
    p_no raiz, recrutado, recrutador;

    scanf("%*s %s %f", nome_recrutador, &valor);
    raiz = cria_no(nome_recrutador, valor);
    mostra_nos_arvore(raiz);

    while (scanf("%s %*s %s %f", nome_recrutador, nome_recrutado, &valor) != EOF)
    {
        recrutado = cria_no(nome_recrutado, valor);
        recrutador = busca_no(raiz, nome_recrutador);
        insere(recrutado, recrutador);
        if (recrutador->esq != NULL && recrutador->dir != NULL)
        {
            remunera_niveis(recrutador->esq);
        }
        mostra_nos_arvore(raiz);
    }

    destroi_arvore(raiz);
    return 0;
}