typedef struct {
    char tipo;
} Bloco;

/**
 * Cria uma matriz de altitudes representando
 * o relevo de um mundo.
 **/
int **calcularAltitudes(int m, int n, int seed);

/**
 * Cria um novo mundo representado por uma matriz
 * de blocos alocada dinamicamente.
 **/
Bloco ***criarMundo(int m, int n, int **altitudes, int seed);

/**
 * Explora o mapa de um mundo e devolve o tempo
 * necessário para minerar todo ele. Além disso,
 * devolve a quantidade de alguns minérios de
 * interesse.
 **/
double explorarMundo(
    Bloco ***mundo, int m, int n, int **altitudes, double tempoPorBloco,
    int *qtdDiamante, int *qtdOuro, int *qtdFerro, int *qtdBlocos);

/* Mostra ao usuário o total de blocos a serem minerados, o tempo total (em segundos) para a sua mineração e a quantidade
  de blocos de diamantes, de ouro e de ferros disponíveis, respectivamente */
void mostrar_informacoes(int *qtdBlocos, double tempo_total, int *qtdDiamante, int *qtdOuro, int *qtdFerro);

/* Libera a memória que foi alocada dinamicamente durante a execução do programa */
void liberar_memoria(int m, int n, Bloco ***mundo, int **altitudes);
