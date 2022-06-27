#include <stdio.h>
#include <string.h>
#include "planejar.h"
#define MAX 100

int main(){

    voos lista_voos[MAX]; 
    int codigo_voo, numero_voos, indice, dia, mes, ano, dia_fim, mes_fim, ano_fim;
    float valor_voo;
    char opcao[MAX], origem[MAX], destino[MAX];

    scanf("%s ", opcao);

    while(1) {
    
        if(strcmp(opcao,"registrar") == 0){

            scanf("%d ", &codigo_voo);
            scanf("%s ", origem);
            scanf("%s ", destino);
            scanf("%d%*c%d%*c%d ", &dia, &mes, &ano);
            scanf("%f", &valor_voo);
            registra_voo(lista_voos, codigo_voo, origem, destino, dia, mes, ano, valor_voo, numero_voos);
            numero_voos+=1;

        } else if(strcmp(opcao,"alterar") == 0){
            scanf("%d %f", &codigo_voo, &valor_voo);
            indice = retorna_indice(lista_voos, numero_voos, codigo_voo);
            altera_valor_voo(lista_voos, indice, valor_voo);

        } else if(strcmp(opcao,"cancelar") == 0){
            scanf("%d ", &codigo_voo);
            indice = retorna_indice(lista_voos, numero_voos, codigo_voo);
            cancela_voo(lista_voos, indice, numero_voos);
            numero_voos-=1;

        } else if(strcmp(opcao,"planejar") == 0){
            scanf("%s", origem);
            scanf("%d%*c%d%*c%d", &dia, &mes, &ano);
            scanf("%d%*c%d%*c%d", &dia_fim, &mes_fim, &ano_fim);
            planejar(lista_voos, origem, dia, mes, ano, dia_fim, mes_fim, ano_fim, numero_voos);
            return 0;
        }

        scanf("%s", opcao);

    }


    return 0;
}