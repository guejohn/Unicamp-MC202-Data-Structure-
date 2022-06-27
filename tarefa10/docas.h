typedef struct container *p_container;
typedef struct doca *p_doca;
typedef struct navio *p_navio;
typedef struct fila *p_fila;

struct doca
{
    int num;
    p_container container_topo;
    int num_containers;
};

struct container
{
    char mercadoria[21];
    p_container prox;
};

typedef struct fila
{
    p_navio ini;
    p_navio fim;

} fila;

struct navio
{
    char nome[21];
    char operacao[11];
    char mercadoria[21];
    int quantidade_restante;
    p_navio prox;
};

/*Cria um novo container alocado dinacamente, com mercadoria igual a 'mercadoria' e retorna seu endereço */
p_container cria_container(char *mercadoria);

/*Empilha, ou seja, insere o 'container' no TOPO da 'doca' */
void empilha_container(p_doca doca, p_container container);

/*Desempilha, ou seja, remove o container do TOPO da 'doca' */
void desempilha_container(p_doca doca);

/*Carrega o navio com os containers de mesma mercadoria do navio, de acordo com a quantidade disponível dessa mercadoria
na doca e exibe a operação no formato:
"{nome do navio} carrega {mercadoria} doca: {numero da doca} conteineres: {numero de containers carregados}" */
void carrega_navio(p_navio navio, p_doca doca);

/*Descarrega os containers do 'navio_atual' na 'doca', de acordo com a 'capacidade_doca' e
exibe a operação no formato:
"{nome do navio} descarrega {mercadoria} doca: {numero da doca} conteineres: {numero de containers descarregados}" */
void descarrega_navio(p_navio navio_atual, p_doca doca, int capacidade_doca);

/*Encontra uma doca disponível que satisfaça a condição da 'operacao' do navio. Quando a operacao é igual a 'carregar',
retorna o endereço da primeira doca com a mercadoria do container do topo da doca igual a 'mercadoria'. Quando é igual
a 'descarregar', retorna o endereço da primeira doca com, pelo menos, o espaço de um container disponível.
Quando não existe a doca necessária, retorna NULL */
p_doca encontra_doca_disponivel(p_doca *vetor_docas, char *operacao, char *mercadoria, int capacidade_doca, int num_docas);

/*Remaneja o navio do INÍCIO para o FIM da fila*/
void navio_fim_fila(p_fila fila);

/*Desenfileira, ou seja, remove o navio do INÍCIO da lista*/
void desenfileira_navio(p_fila fila);

/*Cria uma fila alocada dinamicamente, com inicio e fim iguais a NULL, e retorna seu endereço */
p_fila cria_fila();

/*Enfileira 'navio' na 'fila', isto é, adiciona 'navio' ao FIM da fila*/
void enfileira_navio(p_fila fila, p_navio navio);

/*Cria um navio alocado dinamicamente e retorna o seu endereço */
p_navio cria_navio();

/* Libera o espaço que foi dinamicamente alocado para uma 'fila' de navios, representada por uma lista ligada,
incluindo todos os seus nós */
void destroi_fila_navios(p_fila fila);

/*Gerencia o fluxo do porto, descarregando e carregando os navios. Quando um navio cumpre o seu propósito,
ele é desenfileirado da fila de navios. Se não for possível esvaziar a fila depois de todas operações de carga e descarga,
é exibida uma mensagem: "ALERTA: impossivel esvaziar fila, restam N navios.", onde "N" é o número de navios ainda presentes
na fila */
void gerencia_fluxo(p_fila fila, p_doca *vetor_docas, int capacidade_doca, int num_docas, int num_navios);

/* Cria um vetor alocado dinamicamente com 'num_docas' posicoes, inicializa seus parâmetros
e retorna o ponteiro da primeira posicao */
p_doca *cria_docas(int num_docas);

/*Lê os 'num_navios' navios, criando-os de acordo com os dados lidos, e os enfileira na 'fila_navios' */
void recebe_navios(p_fila fila_navios, int num_navios);

/*Lê os dados do número de docas do porto, a capacidade de containers de cada doca e o número de navios e os
armazena em suas respectivas variáveis */
void le_dados(int *num_docas, int *capacidade_doca, int *num_navios);

/*Libera o espaço alocado dinamicamente para as docas*/
void destroi_docas(p_doca *vetor_docas, int num_docas);