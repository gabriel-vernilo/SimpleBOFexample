# SimpleBOFexample
demonstração de exploração simples de um Buffer Over Flow. O arquivo .c foi criado como exercício do meu Professor de Segurança da Informação : Rafael Sousa


# o que é Buffer Over Flow:

Para entendermos isso antes eu tenho que explicar as coisas um pouco em mais baixo nível (quanto mais baixo o nível mais perto do hardware, linguagem do computador)

Seguinte : o que acontece é que em um programa de alto nível você define uma variável, porém em baixo nível o que realmente acontece é que o processador salva esse valor em um endereço na pilha (pilha é a estrutura onde o pc salva o que ele vai precisar acessar depois, é formada por endereços e esses endereços contêm valores)

Agora podemos falar um pouco mais sobre a falha

# O que acontece no buffer over flow:

O que acontece é que essa falha ocorre quando uma variavel ocupa mais do que ela poderia, em baixo nível, voce empurra mais valores do que endereços para a pilha. Mas entao para onde vão esses valores sem endereço? Eles vao para os endereços que ja estavam na pilha, isso vai desde de endereços de outras variáveis do mesmo prograna até endereços do sistema operacional


# Pratica

# onde está o erro 

![image](https://user-images.githubusercontent.com/53917092/80758242-c557fb00-8b0b-11ea-846f-6d563b97b798.png)

o erro desse código é usar o metodo `gets()` para pegar dados de entrada do usuario e colocar em `char teste[50]` , o erro é no fato de gets nao limitar ou cortar a entrada, e como o tamanho de `teste` está definido para 50, o usuário pode passar desse limite (50 caracteres) e então explorar essa falha

# explorando

O OBJETIVO AQUI É USSAR DO BUFFER OVER FLOW PARA EXECUTAR A FUNÇÃO `vitoria()` MESMO QUE ELA NÃO TENHA SIDO CHAMADA EM NENHUM MOMENTO

uma coisa que acontece em TODAS as funções no seu PC, é que antes de ela ser de fato executada, em baixo nível, ela salva os valores de retorno, isto é, salva onde o código estava executando antes da função ser chamada,

nesse caso, o programa em C, fica mais fácil do que exemplos reais por dois motivos, o primeiro, o endereço de retorno da função `main()` está logo(3 endereços) a baixo de onde estão sendo guardados os valores da variável `teste`, o segundo motivo é, o endereço da função que queremos executar (`vitoria()`) começa com 00, isso facilita pois 00 é o que identifica em baixo nivel o final de uma string, como nós passamos o endereço de trás para frente (e em hexadecimal) o 00 ficará no final, e o programa ainda rodará pois vai realmente achar que é uma String. obs: repare que no `exploit.py` na variavel que guarda o endereço que queremos executar eu nao coloquei o 00 por conta disso

então, agora prenceremos todos os 50 espaços de "teste" e dos outros endereços até chegar no endereço que guarda o endereço de retorno do fim da função `main()`

![image](https://user-images.githubusercontent.com/53917092/80759979-8a0afb80-8b0e-11ea-80b0-06ea91defb55.png)

nessa imagem eu coloquei exatamente 50 vezes a letra "A" (41, em hexadecimal na tabela ASCII), então podemos observar que o endereço de retorno está 3 endereços para baixo ainda, ou seja, mais 12 caracteres (visto que cada um ocupa dois espaços do enderço, como visto na ultima imagem), depois desse 12, colocamos os 4 que serão o novo endereço

para fazer isso eu usei o `exploit.py`, ele usa o comando `ECHO` (presente em windows e linux) e ` | ` para enviar esse caracteres para `bof.exe`.

![image](https://user-images.githubusercontent.com/53917092/80760500-62686300-8b0f-11ea-9110-ed606a4f362a.png)

(vemos uma execução normal, e uma usando o exploit, que esta executa a função que apesar de nao ser chamada, esta na memoria)

# Como evitar esse erro

Neste caso seria bem simples, substituindo a função `gets(teste)`  para `fgets(teste,49,stdin)` isso seria corrigido.

explicando um pouco melhor o `fgets()`, ele tem 3 parametros, a variavel que vai guardar o valor, o numero limite(LEMBRE DE COLOCAR UM A MENOS DO QUE A VARIAVEL SUPORTA PARA QUE O SISTEMA COLOQUE O 00 INDICANDO FINAL DE STRING), e o jeito que ela vai receber, podendo ser por exemplo por `stdin` (standard input: entrada padrão) que seria pelo terminal, ou por ponteiros que apontam para arquvos para o fgets ler

