typedef struct no_codigo *p_noc;
typedef struct no_oferta *p_noo;

struct no_codigo
{
    int codigo_produto;
    p_noc esq;
    p_noc dir;
    p_noo raiz_ofertas;
};
struct no_oferta
{
    char nome_empresa[30];
    float preco_produto;
    p_noo esq;
    p_noo dir;
};

/* Cria e aloca dinamicamente um novo nó de oferta e retorna o seu endereço */
p_noo cria_no_ofertas(char *nome_empresa, float preco);

/* Cria e aloca dinamicamente um novo nó de código e retorna o seu endereço */
p_noc cria_no_codigo(int codigo);

/*Insere a nova oferta, que inclui o nome da empresa e o preço do produto, na árvore binária de busca de ofertas
- representada por 'raiz' - e retorna a raiz da árvore com a nova oferta inclusa. */
p_noo insere_oferta(p_noo raiz, char *nome_empresa, float preco);

/*Insere 'codigo' na árvore binária de busca de códigos, representada por 'raiz', e retorna a raiz da árvore
com o novo código incluso. Se o código já estiver presente na árvore, simplesmente retorna a raiz original */
p_noc insere_codigo(p_noc raiz, int codigo);

/* Busca o nó de código igual a 'codigo' na árvore binária de busca de códigos, e retorna o seu endereço.
Se o código não existir na árvore, retornará NULL */
p_noc busca_no(p_noc raiz, int codigo);

/*Lê os 'num_anuncios' anuncios, compostos pelo nome da empresa, o código do produto e o preço do produto. 
Depois, insere o código de cada produto em uma árvore de raiz igual a 'raiz_c' e insere as ofertas,
com o nome da empresa e o preço do produto, em uma árvore de ofertas daquele código de produto. */
p_noc recebe_anuncios(int num_anuncios, p_noc raiz_c);

/* Imprime, em ordem lexicográfica do nome de empresa, todas as ofertas da árvore binária de busca de ofertas - representada por 'raiz' - que satisfaçam a condição do preço do produto ser até 110% do valor de oferta, no formato
"{nome_empresa} {codigo produto} {valor_produto}" */
void imprime_ordenado(p_noo raiz, int codigo_produto, float valor_oferta, int *oferta_encontrada);

/*Lê 'num_buscas' buscas e mostra as ofertas encontradas, no formato "{nome_empresa} {codigo_produto} {preco_produto}", de acordo com o codigo do produto e o valor da oferta lidos (considera-se dentro do valor da oferta um valor de produto até
110% do valor de oferta).
Se nenhuma oferta for encontrada, mostra-se "nenhuma boa oferta foi encontrada" */
void busca_ofertas(int num_buscas, p_noc raiz_c);

/*Destrói a árvore binária de ofertas, liberando o espaço de todos os seus nós.*/
void destroi_arvore_ofertas(p_noo raiz);

/*Destrói a árvore binária de códigos e a de ofertas, liberando todos os seus nós*/
void destroi_arvore(p_noc raiz);

