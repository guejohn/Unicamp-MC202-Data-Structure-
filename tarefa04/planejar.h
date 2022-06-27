#define MAX 100

typedef struct {
    int codigo;
    char origem[MAX];
    char destino[MAX];
    int dia;
    int mes;
    int ano;
    float valor;
} voos;


int retorna_indice( voos lista_voos[], int numero_voos, int codigo_voo);

int compara_datas(int d1,int m1, int y1, int d2, int m2,int y2);

int verifica_intervalo(int dia1, int mes1, int ano1, int dia2, int mes2, int ano2, char sinal);

void planejar( voos lista_voos[], char origem[], int dia_inicio, int mes_inicio, int ano_inicio, int dia_fim, int mes_fim, int ano_fim, int num_voos);

void cancela_voo( voos lista_voos[], int indice_voo, int numero_voos);

void altera_valor_voo( voos lista_voos[], int indice_voo, float novo_valor);

void registra_voo( voos lista_voos[], int codigo_voo, char origem_voo[], char destino_voo[], int dia_voo, int mes_voo, int ano_voo, float valor_voo, int indice_voo);
