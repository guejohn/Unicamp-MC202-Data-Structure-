#include <stdio.h>
#include <math.h>
#define MAX 1000

double calcula_imposto_anual(double valor, double abatimento){

    /* Calcula o imposto anual de um funcionário com base nos seus 12 meses de recebimento */

    double min_intervalos[5] = {0, 18000.0, 26400.0, 36000.0, 44400.0};
    double aliquotas[5] ={0.0, 7.5, 15.0, 22.5, 27.5}; 
    double soma = 0.0;
    int i = 4;

    valor = valor - abatimento;

    while (i >= 0){
        if (valor > min_intervalos[i]){
            soma += (valor - min_intervalos[i]) * (aliquotas[i]/100);
            valor = min_intervalos[i];
        } 
        i = i - 1;
    }
    return soma;
}


double calcula_imposto_mensal(double valor){

    /* Calcula o imposto mensal de um funcionário com base no recebimento de 1 mês */

    double min_intervalos[5] = {0, 1499.15, 2246.75, 2995.70, 3743.19};
    double aliquotas[5] ={0.0, 7.5, 15.0, 22.5, 27.5}; 
    double soma = 0.0;
    int i = 4;
    
    while (i >= 0){
        if (valor > min_intervalos[i]){
            soma += (valor - min_intervalos[i]) * (aliquotas[i]/100);
            valor = min_intervalos[i];
        } 
        i = i - 1;
    }
    return soma;
}

void calcula_imposto_renda(int num_funcionarios, double soma_imposto_mensal[], double rendimentos_mensais[][12], double imposto_mensal[][12], double imposto_anual[], double ajuste[], double abatimentos[]){

    /* Dados os rendimentos mensais de cada funcionário, calcula, organiza e guarda, para cada funcionário, os impostos retidos em cada mês,
    o total retido na fonte, o imposto devido anual e o valor do ajuste. */

    double soma_rendimentos;

    for(int i=0; i < num_funcionarios; i++){
        soma_rendimentos = 0;
        soma_imposto_mensal[i] = 0;
        for(int j=0; j < 12; j++){
            soma_rendimentos += rendimentos_mensais[i][j];
            imposto_mensal[i][j] = calcula_imposto_mensal(rendimentos_mensais[i][j]);
            soma_imposto_mensal[i] += imposto_mensal[i][j];
        }
        imposto_anual[i] = calcula_imposto_anual(soma_rendimentos, abatimentos[i]);
        ajuste[i] = imposto_anual[i] - soma_imposto_mensal[i];
    }
}

void mostra_dados_imposto(int num_funcionarios, double imposto_mensal[][12], double imposto_anual[], double ajuste[], double soma_imposto_mensal[]){
    
    /* Exibe os dados de imposto de todos os funcionários em forma de tabela, cujas as doze primeiras colunas correspondem
    aos impostos retidos em cada mês e cujas as últimas colunas correspondem ao total retido na fonte, ao imposto devido anual
    e ao valor do ajuste*/
    
    printf("\n");
    printf("Jan	Fev	Mar	Abr	Mai	Jun	Jul	Ago	Set	Out	Nov	Dez	Retido	Devido	Ajuste\n");
   
    for(int i=0; i < num_funcionarios; i++){
        for(int j=0; j < 12; j++){
            printf("%.2lf ", imposto_mensal[i][j]);
        }
        printf("%.2lf ", soma_imposto_mensal[i]);
        printf("%.2lf ", imposto_anual[i]);
        printf("%.2lf\n", ajuste[i]);
    }

}
void le_dados(int num_funcionarios, double rendimentos_mensais[][12], double abatimentos[]){

    /*Lê, em cada linha, os dados de rendimentos de cada funcinário relativo aos 12 meses do ano e, posteriormente,
    os valores de abatimento de cada funcionário, em ordem. Armazena os dados em duas matrizes: rendimentos_mensais e abatimentos*/

    for(int i=0; i < num_funcionarios; i++){
        for(int j=0; j < 12; j++){
            scanf("%lf", &rendimentos_mensais[i][j]);
        }
    }
    for(int i=0; i < num_funcionarios; i++){
        scanf("%lf", &abatimentos[i]);
        }
    }


int main(){
    
    int num_funcionarios;
    double rendimentos_mensais[MAX][12], abatimentos[MAX];
    double soma_imposto_mensal[MAX], imposto_anual[MAX], ajuste[MAX], imposto_mensal[MAX][12];

    scanf("%d", &num_funcionarios);

    le_dados(num_funcionarios, rendimentos_mensais, abatimentos);
    calcula_imposto_renda(num_funcionarios, soma_imposto_mensal,rendimentos_mensais, imposto_mensal, imposto_anual, ajuste, abatimentos);
    mostra_dados_imposto(num_funcionarios, imposto_mensal, imposto_anual, ajuste, soma_imposto_mensal);


    return 0;
}

