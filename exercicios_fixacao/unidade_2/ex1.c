/*
Questão 1.Enquanto os tipos numéricos em Python são relativamente simples:

int,float ou complex, em C a situação é mais complicada. Não há tipo complexo na versão mais antiga, 
temos vários tipos inteiros diferentes, que permitem armazenar intervalos diferentes, podem ter ou não sinal,
além de pelo menos dois tipos de números de ponto flutuante.  Escolha um tipo de variável adequado para armazenar as
seguintes informações dependendo da situação e tente explicar a sua razão:

(a) A idade de uma pessoa em um formulário para um banco de dados com milhões de registros.

Utilizaria inteiro, já que cobre bem a perspectiva de 0 a 150.

(b) A idade de uma pessoa em dias para um programa em que desejamos somar ou subtrair um número arbitrário de dias.

Utilizaria inteiro, já que os dias não podem ser quebrados.

(c) A nota de um estudante.

Float, já que a nota pode ter casas decimais mas não exige tanto espaço.

(d) A quantidade de chuva média no mês de fevereiro.

Inteiro, já que normalmente não há casas decimais.

(e) O ângulo de rotação de um robô cirurgião a ser transmitido pela internet.

Double, já que pode ter muitas casas decimais e exigir maior espaço.

(f) O tamanho do seu quintal.

Float, já que pode ter casas decimais mas não exige tanto espaço.

(g) O número de estrelas do universo.

Notação científica, já que o número tende ao infinito.

(h) O saldo da conta bancária.

Float, por não exigir tanto espaço.

(i)A posição de uma partícula em um jogo de alta resolução.

Double por poder exigir muito espaço.

(j)Uma sequência de números inteiros representando as escolhas

Inteiro, pois não exige tanto espaço.
*/