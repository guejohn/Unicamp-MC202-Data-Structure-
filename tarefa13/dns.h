enum cor
{
    VERMELHO,
    PRETO
};

typedef struct no_dominio *p_nod;
typedef struct no_usuario *p_nou;

struct no_dominio
{
    char dominio[101];
    char servidor_DNS[20];
    enum cor cor;
    p_nod esq;
    p_nod dir;
};
struct no_usuario
{
    char ip[20];
    int num_consultas;
    enum cor cor;
    p_nou esq;
    p_nou dir;
};

/* Cria e aloca dinamicamente um novo nó de domínio e retorna o seu endereço */
p_nod cria_no_dominio(char *dominio, char *servidor_DNS);

/* Cria e aloca dinamicamente um novo nó de usuário e retorna o seu endereço */
p_nou cria_no_usuario(char *ip);

/* Busca o nó_dominio de domínio igual a 'domínio' na árvore binária de busca de domínios, e retorna o seu endereço.
Se o domínio não existir na árvore, retornará NULL */
p_nod busca_no_dominio(p_nod raiz, char *dominio);

/* Busca o nó_usuário de ip igual a 'ip' na árvore binária de busca de usuários, e retorna o seu endereço.
Se o ip não existir na árvore, retornará NULL */
p_nou busca_no_usuario(p_nou raiz, char *ip);

/* Verifica se a cor do nó de DOMÍNIO é vermelha. Se o nó for nulo, tem-se por convenção de árvore rubro-negra que sua cor
deve ser preta e, portanto, retorna 0. Do contrário, se o nó não for nulo, retorna 1 se a cor for vermelha e 0 se não for. */
int ehVermelho_d(p_nod no_d);

/* Verifica se a cor do nó de USUÁRIO é vermelha. Se o nó for nulo, tem-se por convenção de árvore rubro-negra que sua cor
deve ser preta e, portanto, retorna 0. Do contrário, se o nó não for nulo, retorna 1, se a cor for vermelha, e 0, se não for. */
int ehVermelho_u(p_nou no_u);

/* Verifica se a cor do nó de DOMÍNIO é preta. Se o nó for nulo, tem-se por convenção de árvore rubro-negra que sua cor deve ser
preta e, portanto, retorna 1. Do contrário, se o nó não for nulo, retorna 0, se a cor não for preta, e 1, se for. */
int ehPreto_d(p_nod no_d);

/* Verifica se a cor do nó de USUÁRIO é preta. Se o nó for nulo, tem-se por convenção de árvore rubro-negra que sua cor
deve ser preta e, portanto, retorna 1. Do contrário, se o nó não for nulo, retorna 0, se a cor não for preta, e 1, se for. */
int ehPreto_u(p_nou no_u);

/*Rotaciona a árvore de busca binário rubro-negra de DOMÍNIOS - representada por 'raiz' - para a esquerda, isto é, a nova raiz
é a filha direita da raiz original, a raiz original vira filha esquerda da nova raiz e a filha esquerda da raiz original vira
filha esquerda da filha esquerda da nova raiz */
p_nod rotaciona_para_esquerda_d(p_nod raiz);

/*Rotaciona a árvore de busca binário rubro-negra de USUÁRIOS - representada por 'raiz' - para a esquerda, isto é, a nova raiz
é a filha direita da raiz original, a raiz original vira filha esquerda da nova raiz e a filha esquerda da raiz original vira
filha esquerda da filha esquerda da nova raiz */
p_nou rotaciona_para_esquerda_u(p_nou raiz);

/*Rotaciona a árvore de busca binário rubro-negra de DOMÍNIOS - representada por 'raiz' - para a direita, isto é, a nova raiz é
a filha esquerda da raiz original, a raiz original vira filha direita da nova raiz e a filha direita da raiz original vira filha
direita da filha direita da nova raiz */
p_nod rotaciona_para_direita_d(p_nod raiz);

/*Rotaciona a árvore de busca binário rubro-negra de USUÁRIOS - representada por 'raiz' - para a direita, isto é, a nova raiz é
a filha esquerda da raiz original, a raiz original vira filha direita da nova raiz e a filha direita da raiz original vira filha
direita da filha direita da nova raiz */
p_nou rotaciona_para_direita_u(p_nou raiz);

/* Modifica a cor do nó_dominio 'raiz' para vermelho e a cor de seus dois nós filhos para preto */
void sobe_vermelho_d(p_nod raiz);

/* Modifica a cor do nó_usuario 'raiz' para vermelho e a cor de seus dois nós filhos para preto */
void sobe_vermelho_u(p_nou raiz);

/*Insere o domínio, representado por um endereço de domínio e um endereço de servidor DNS associado, na árvore binária
de busca balanceada rubro-negra de domínios, representada por 'raiz', e retorna a raiz da árvore com o novo domínio incluso.*/
p_nod insere_dominio(p_nod raiz, char *dominio, char *servidor_DNS);

/*Insere o usuário, representado por um endereço IP, na árvore binária de busca balanceada rubro-negra de usuários, 
representada por 'raiz', e retorna a raiz da árvore com o novo usuário incluso. Se o IP já estiver presente na árvore,
simplesmente retorna a raiz original */
p_nou insere_usuario(p_nou raiz, char *ip);

/*Lê os 'num_dominios' dominios, compostos por um endereço de domínio e por um endereço de um servidor DNS associado. 
Depois, insere os domínios na árvore binária balanceada rubro-negra de domínios, representada por 'raiz_d' */
p_nod recebe_dominios(int num_dominios, p_nod raiz_d);

/*Lê as 'num_consultas', compostas por um domínio e pelo ip do usuário que realiza a consulta e imprime:
- "NOTFOUND {dominio} FROM {ip_usuario}" se o domínio consultado não existe;
- "ACCEPTED {dominio} FROM {ip_usuario} RESPOND {servidor_DNS_associado}" se o domínio consultado foi encontrado e o
usuário não ultrapassou o limite de consultas ('max_consultas_usuario') estabelecido;
- "FORBIDDEN {dominio} FROM {ip_usuario}" se o usuário ultrapassou o limite de consultas estabelecido. */
p_nou realiza_consultas(int num_consultas, int max_consultas_usuario, p_nod raiz_d, p_nou raiz_u);

/*Destrói a árvore binária de domínios, liberando o espaço de todos os seus nós.*/
void destroi_arvore_dominios(p_nod raiz);

/*Destrói a árvore binária de usuários, liberando o espaço de todos os seus nós.*/
void destroi_arvore_usuarios(p_nou raiz);