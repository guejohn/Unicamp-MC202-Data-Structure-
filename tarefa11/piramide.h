typedef struct no *p_no;

struct no
{
    char nome[21];
    float valor;
    p_no esq;
    p_no dir;
    p_no pai;
};

/* Remunera até seis níveis da pirâmide (representada por uma árvore), seguindo a seguinte regra:
Cada um dos dois novos participantes paga 6% do seu capital para o recrutador, que depois paga 5%
do seu capital para seu próprio recrutador, que depois paga 4% e assim por diante... */
void remunera_niveis(p_no no);

/* Insere o nó 'filho' abaixo do nó 'pai' e acrescenta ao valor de investimento do 'filho'
a bonificação de 10% de seu investimento inicial, que é descontado do nó 'pai' */
void insere(p_no filho, p_no pai);

/* Calcula a altura de uma árvore e retorna o seu valor */
int calcula_altura(p_no raiz);

/* Exibe todos os nós do nível 'nivel' no formato
"[nome_do_no valor_do_no]", para cada nó do nível,
da esquerda para a direita */
void imprime_nos_nivel(p_no raiz, int nivel);

/*Mostra todos os nós de uma árvore, por nível.*/
void mostra_nos_arvore(p_no raiz);

/*Busca o nó contido na árvore com o nome igual a 'nome' e retorna o seu endereço*/
p_no busca_no(p_no raiz, char *nome);

/*Cria e aloca um nó dinamicamente, como nome igual a 'nome' e valor igual a 'valor, e retorna o seu endereço*/
p_no cria_no(char *nome, float valor);

/*Destrói uma árvore binária, liberando o espaço de todos os seus nós, a partir do nó raiz.*/
void destroi_arvore(p_no raiz);