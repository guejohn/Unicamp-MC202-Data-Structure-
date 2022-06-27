#include <stdio.h>
#include <string.h>
#include "planejar.h"
#define MAX 100

int retorna_indice( voos lista_voos[], int numero_voos, int codigo_voo) {
    
  /* Retorna o índice de 'codigo_voo' na 'lista'. Caso não conste, retorna 0 */

  for (int i = 0; i < numero_voos; i++) {

    if (lista_voos[i].codigo == codigo_voo) {

      return i;
    }
  }
  return 10;
}

int compara_datas(int d1,int m1, int y1, int d2, int m2,int y2){

    int x1=0;
    int x2=0;

    m1 = (m1 + 9) % 12;
    y1 = y1 - m1 / 10;
    x1= 365*y1 + y1/4 - y1/100 + y1/400 + (m1*306 + 5)/10 + ( d1 - 1 );

    m2 = (m2 + 9) % 12;
    y2 = y2 - m2 / 10;
    x2= 365*y2 + y2/4 - y2/100 + y2/400 + (m2*306 + 5)/10 + ( d2 - 1 );

    return x2 - x1;
}

int verifica_intervalo(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2, char sinal){
    
    if (sinal == '+'){
        if(ano1>ano2){
            return 1;
        }else if((ano1==ano2) && (mes1 > mes2)){
            return 1;
        }else if((ano1==ano2) && (mes1 == mes2) && (dia1>=dia2)){
            return 1;
        }
    }
    else if (sinal == '-'){
        if(ano1<ano2){
            return 1;
        }else if((ano1==ano2) && (mes1 < mes2)){
            return 1;
        }else if((ano1==ano2) && (mes1 == mes2) && (dia1<=dia2)){
            return 1;
        }
    }

    return 0;
}

void planejar( voos lista_voos[], char origem[], int dia_inicio, int mes_inicio, int ano_inicio, int dia_fim, int mes_fim, int ano_fim, int num_voos){

    int voo_origem, voo_retorno, flag = 0;
    float preco_viagem;

    for(int i = 0; i < num_voos; i++){
        if((strcmp(origem, lista_voos[i].origem)==0)){
            for(int j = 0; j < num_voos; j++){
                if((strcmp(lista_voos[j].destino, origem)==0) && (strcmp(lista_voos[i].destino, lista_voos[j].origem)==0)){
                    int diferenca_dias = compara_datas(lista_voos[i].dia, lista_voos[i].mes, lista_voos[i].ano, lista_voos[j].dia, lista_voos[j].mes, lista_voos[j].ano);
                    if(diferenca_dias >2){
                        if(verifica_intervalo(lista_voos[i].dia, lista_voos[i].mes, lista_voos[i].ano, dia_inicio, mes_inicio, ano_inicio,'+')==1){
                            if(verifica_intervalo(lista_voos[j].dia, lista_voos[j].mes, lista_voos[j].ano, dia_fim, mes_fim, ano_fim,'-')==1){
                                if (flag == 0){
                                    voo_origem = lista_voos[i].codigo;
                                    voo_retorno = lista_voos[j].codigo;
                                    preco_viagem = lista_voos[i].valor + lista_voos[j].valor;
                                    flag = 1;
                                }
                                else if(flag == 1 && ((lista_voos[i].valor + lista_voos[j].valor) < preco_viagem)){
                                    voo_origem = lista_voos[i].codigo;
                                    voo_retorno = lista_voos[j].codigo;
                                    preco_viagem = lista_voos[i].valor + lista_voos[j].valor;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
        printf("%d\n%d\n", voo_origem, voo_retorno);
}

void cancela_voo( voos lista_voos[], int indice_voo, int numero_voos){

    for(int i = indice_voo; i < numero_voos; i++){
        lista_voos[i] = lista_voos[i+1];
    }
}
void altera_valor_voo( voos lista_voos[], int indice_voo, float novo_valor){
    
    lista_voos[indice_voo].valor = novo_valor;

}
void registra_voo( voos lista_voos[], int codigo_voo, char origem_voo[], char destino_voo[], int dia_voo, int mes_voo, int ano_voo, float valor_voo, int indice_voo){

    lista_voos[indice_voo].codigo = codigo_voo;
    strcpy(lista_voos[indice_voo].origem, origem_voo);
    strcpy(lista_voos[indice_voo].destino, destino_voo);
    lista_voos[indice_voo].dia = dia_voo;
    lista_voos[indice_voo].mes = mes_voo;
    lista_voos[indice_voo].ano = ano_voo;
    lista_voos[indice_voo].valor = valor_voo;
}