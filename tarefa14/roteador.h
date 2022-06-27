typedef struct fila_prioridade *p_fp;
typedef struct pacote *p_pacote;

typedef struct pacote
{
    int id;
    int prioridade;
    int incremento;

} pacote;

struct fila_prioridade
{
    pacote *v;
    int tamanho;
    int capacidade;
};
#define pai(i) ((i - 1) / 2)
#define filho_esq(i) (2 * i + 1)
#define filho_dir(i) (2 * i + 2)

/* Cria uma fila de prioridade e retorna o seu endereço */
p_fp cria_fila_prioridade(int capacidade);

/* Cria um pacote, contendo seu id, prioridade e incremento, e retorna o seu endereço */
p_pacote cria_pacote(int id, int prioridade, int incremento);

/* Troca os pacotes de posição, isto é, coloca o pacote que estava no endereço de 'pacote1' no endereço do 'pacote2' e o
pacote que estava no endereço do 'pacote2' no endereço do 'pacote1' */
void troca_pacotes(pacote* pacote1, pacote* pacote2);

/* Sobe o pacote na fila de prioridades quando está em um posição incorreta, isto é, quando está abaixo de pacotes
com menor prioridade do que a sua, até que atinja a posição correta*/
void sobe_pacote_fila(p_fp fila, int indice_pacote);

/* Desce o pacote na fila de prioridades quando está em um posição incorreta, isto é, quando está acima de pacotes
com maior prioridade do que a sua, até que atinja a posição correta*/
void desce_pacote_fila(p_fp fila, int indice_pacote);

/*Insere 'pacote' na fila e reorganiza a sua posição até que não fique abaixo de nenhum pacote com menor prioridade
que a sua */
void insere_fila(p_fp fila, pacote pacote);

/* Extrai o pacote de maior prioridade da fila de prioridades, retornando-o. Troca o primeiro elemento
com o último, decrementa 1 do tamanho da lista e reorganiza a fila de forma com que o pacote agora em primeira posição não 
fique acima de algum pacote com maior prioridade que a sua, respeitando a estrutura de max-heap. */
pacote extrai_maximo(p_fp fila);

/* Emite um tick, imprimindo os dados de id, prioridade e incremento dos pacotes liberados - sendo o máximo o
'max_pacotes_enviar' - e os extraindo da lista */
void emite_tick(p_fp fila, int max_pacotes_enviar, int num_ticket);

/* Atualiza a prioridade dos pacotes remanescentes da fila para a prioridade atual do pacote + o incremento do pacote */
void atualiza_prioridade(p_fp fila);

/* Recebe os dados dos pacotes, os insere na fila de prioridade e emite um tick quando os dados forem
iguais a '0 0 0', atualizando as prioridades dos pacotes remanescentes para a prioridade atual do pacote + o incremento do
pacote. */
void recebe_informacoes(p_fp fila, int capacidade_fila, int max_pacotes_enviar);

/* Destroi a fila de prioridades, liberando o espaço que foi alocado dinamicamente */
void destroi_fila(p_fp fila);
