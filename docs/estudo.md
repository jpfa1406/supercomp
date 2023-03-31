# Estudo PI

## Defina um problema difícil computacionalmente:

Problemas considerados difíceis computacionalmente são aqueles em que não há algoritmo conhecido que possa resolvê-los em __tempo polinomial__ (ou seja, em tempo razoável para entradas grandes). Para resolver esses problemas, geralmente é necessário utilizar __heurísticas__ ou algoritmos de aproximação, que fornecem __soluções sub-ótimas__ em tempo razoável.

## Qual o papel das heurísticas na abordagem de obter soluções para problemas computacionalmente difíceis?

As __heurísticas__ são técnicas utilizadas para encontrar soluções aproximadas para problemas computacionalmente difíceis, quando não é possível encontrar uma solução exata em tempo razoável. O papel das heurísticas é fornecer uma solução aproximada para o problema, que pode ser utilizada como uma __boa aproximação da solução ideal__ em muitos casos. Porém, é importante destacar que as soluções obtidas por meio de heurísticas __não são garantidamente ótimas__, e podem ser menos precisas do que as soluções exatas, mas ainda assim fornecem uma boa aproximação e podem ser muito úteis em muitas situações.

## A heurística gulosa tem alguma garantia de otimalidade?

Não, a heurística gulosa __não tem garantia de otimalidade__. A abordagem gulosa é uma técnica heurística que segue uma estratégia de seleção de soluções que parecem ser ótimas a cada passo, sem considerar o impacto de suas escolhas no resultado final. Em outras palavras, a heurística gulosa faz escolhas __locais ótimas__, com a expectativa de que essas escolhas conduzam a uma __solução global ótima__. No entanto, essa abordagem não garante que a solução obtida seja ótima, nem fornece uma estimativa precisa do quão longe a solução está do __ótimo global__.

## Qual o papel que a aleatoriedade exerce em problemas de combinação discretos?

A aleatoriedade pode fornecer uma estratégia para __explorar__ diferentes regiões do __espaço de soluções__ e evitar ficar preso em __ótimos locais__ ou soluções subótimas. Em outras palavras, a aleatoriedade pode ajudar a escapar de soluções locais ótimas e encontrar soluções globalmente melhores.

Em alguns casos, a aleatoriedade pode ser usada para gerar soluções iniciais aleatórias para o problema e, em seguida, aplicar __heurísticas determinísticas__ ou __métodos de busca local__ para refiná-las e melhorar sua qualidade. Em outros casos, a aleatoriedade pode ser incorporada diretamente na __heurística__, por exemplo, através da introdução de operadores de __mutação__ ou __crossover__ aleatórios em algoritmos genéticos ou algoritmos evolutivos.

## A heurística de busca local apresenta vantagens em relação à heurística gulosa?

Sim, a heurística de __busca local__ apresenta algumas vantagens em relação à heurística __gulosa__. Enquanto a heurística gulosa toma decisões com base na escolha localmente ótima em cada etapa do processo de construção da solução, a busca local é uma técnica que tenta melhorar iterativamente uma solução inicial por meio da __exploração de vizinhanças próximas__.

## No Valgrind, qual o papel do indicador IR?

No Valgrind, o indicador IR significa __"Instruction Reads"__ (leituras de instruções) e é uma das estatísticas de desempenho coletadas pelo Valgrind. Ele representa o número de leituras de instruções feitas pela CPU enquanto o programa é executado em um ambiente simulado pelo Valgrind. Essa informação é útil para entender como o código está sendo executado e para identificar possíveis __gargalos de desempenho__, como laços de repetição ineficientes ou acessos desnecessários à memória.

## Se um problema é 30% sequencial, qual o speedup máximo que ele pode ter ao paralelizarmos?

Se um problema é 30% sequencial, isso significa que apenas 70% do problema pode ser paralelizado, já que 30% do tempo de execução será sempre sequencial e não poderá ser acelerado pelo paralelismo.

- O speedup máximo que poderíamos alcançar seria dado pela Lei de Amdahl, que é dada pela fórmula:

- Speedup máximo = 1 / (1 - P), onde P é a fração sequencial do problema.

- Substituindo os valores, temos:

- Speedup máximo = 1 / (1 - 0,3) = 1 / 0,7 = 1,43

Portanto, o speedup máximo que poderíamos alcançar seria de 1,43 vezes, ou seja, uma aceleração de até 43% em relação à versão sequencial do problema. Note que esse valor é um limite superior teórico, e o speedup real alcançado pode ser menor devido a fatores como a sobrecarga de comunicação entre as partes paralelas e outras limitações do sistema.

## Quais vantagens e desvantagens da passagem de parâmetros por referência?

A passagem de parâmetros por referência é uma técnica utilizada em linguagens de programação para que uma função possa __acessar e modificar__ o valor de uma variável ou objeto que está fora do seu escopo.

**Vantagens:**

- __Economia de memória:__ como a função recebe uma referência ao valor original, e não uma cópia do valor, é possível economizar memória.
- __Eficiência:__ a passagem de parâmetros por referência pode ser mais rápida do que a passagem por valor em alguns casos.
- __Modificação do valor original:__ a função pode modificar o valor original do objeto ou variável, o que é útil em situações em que se deseja alterar o estado de um objeto ou retornar mais de um valor da função.

**Desvantagens:**

- __Alterar objeto original:__ a função pode inadvertidamente modificar o valor original do objeto.
- __Risco de vazamentos de memória:__ se a função não for cuidadosamente implementada, pode ocorrer o risco de vazamento de memória.

## Na aula sobre valgrind, nós vimos formas diferentes de somar os números de uma matriz. Qual a razão para a diferença de performance?

O problema é a gravação na memória do array: x[i][j]. Aqui está um pouco de perspectiva sobre o porquê:  

Você tem um array bidimensional, mas a memória do computador é inerentemente unidimensional. Então, embora você imagine seu array assim:

```
0,0 | 0,1 | 0,2 | 0,3
----+-----+-----+----
1,0 | 1,1 | 1,2 | 1,3
----+-----+-----+----
2,0 | 2,1 | 2,2 | 2,3
```

Seu computador armazena isso na memória como uma única linha:

```
0,0 | 0,1 | 0,2 | 0,3 | 1,0 | 1,1 | 1,2 | 1,3 | 2,0 | 2,1 | 2,2 | 2,3
```

No segundo exemplo, você acessa o array fazendo um loop sobre o segundo número primeiro, ou seja:

```
x[0][0] 
        x[0][1]
                x[0][2]
                        x[0][3]
                                x[1][0] etc...
```

O que significa que você está acessando todos eles em ordem. Agora olhe para a primeira versão. Você está fazendo:

```
x[0][0]
                                x[1][0]
                                                                x[2][0]
        x[0][1]
                                        x[1][1] etc...
```

Devido à maneira como C organizou o array bidimensional na memória, você está pedindo para ele pular para todo lugar. Mas agora vem a surpresa: Por que isso importa? Todos os acessos à memória são iguais, certo?

Não, por causa das caches. Os dados da memória são trazidos para a CPU em pequenos pacotes (chamados de "linhas de cache"), geralmente com 64 bytes. Se você tem inteiros de 4 bytes, isso significa que você está recebendo 16 inteiros consecutivos em um pacote organizado. É na verdade bastante lento buscar esses pacotes de memória; a CPU pode fazer muito trabalho no tempo que leva para carregar uma única linha de cache.

Agora olhe de volta para a ordem dos acessos: O segundo exemplo está (1) pegando um pacote de 16 inteiros, (2) modificando todos eles, (3) repetindo 4000*4000/16 vezes. Isso é agradável e rápido, e a CPU sempre tem algo para trabalhar.

O primeiro exemplo está (1) pegando um pacote de 16 inteiros, (2) modificando apenas um deles, (3) repetindo 4000*4000 vezes. Isso vai exigir 16 vezes mais "buscas" na memória. Sua CPU na verdade terá que gastar tempo esperando que essa memória apareça, e enquanto isso estiver acontecendo, você está perdendo um tempo valioso.

## Como se dá a heurística por algoritmos genéticos? Qual o papel da mutação?

A heurística por algoritmos genéticos utiliza operações de seleção, cruzamento e mutação para gerar novas __soluções candidatas__ para um determinado problema. Inicialmente, é criada uma população de soluções aleatórias. Em seguida, é realizada uma avaliação de cada solução candidata, atribuindo-lhe um valor de __aptidão__ ou __fitness__, que indica o quão boa é aquela solução em relação ao problema em questão.

A partir da avaliação, é selecionada uma parte da população (normalmente as soluções mais aptas) para __cruzamento__. O cruzamento consiste em __combinar características__ de duas ou mais soluções, gerando uma nova solução candidata. Por fim, é realizada uma __mutação__, que introduz uma pequena alteração __aleatória__ em algumas das características da solução gerada pelo cruzamento. Esse processo é repetido até que uma solução satisfatória seja encontrada ou que o número máximo de iterações seja atingido.

O papel da mutação é introduzir diversidade na população, evitando que todas as soluções se tornem muito semelhantes umas às outras. Sem mutação, a busca por soluções ótimas poderia ficar presa em um mínimo local, sem conseguir explorar outras regiões do espaço de soluções.

## Na busca exaustiva, a profundidade de busca afeta consideravelmente o resultado obtido. Explique com suas palavras a importância de se buscar conhecer uma profundidade razoável de busca?

A profundidade de busca na busca exaustiva é um fator crucial para obter resultados satisfatórios. Se a profundidade for muito rasa, o algoritmo pode não ser capaz de explorar todas as soluções possíveis e, portanto, pode não encontrar a solução ótima. Por outro lado, se a profundidade for muito grande, o algoritmo pode levar muito tempo para explorar todas as soluções possíveis, uma fez que a arvore cresce __exponecialmente__ em relação a __profundidade__, o que pode não ser viável em termos de tempo e recursos computacionais.

## Explore x Exploit

"Explore" se refere a uma estratégia que envolve explorar novas opções e adquirir novas informações para reduzir a incerteza ou aumentar o conhecimento sobre o ambiente ou o problema em questão. (__aumentar espaço de soluções__)

"Exploit" se refere a uma estratégia que envolve aproveitar ao máximo as informações existentes e as opções conhecidas para maximizar a recompensa ou minimizar a perda.

