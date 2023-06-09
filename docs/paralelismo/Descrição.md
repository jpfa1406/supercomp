# Descrição

## Paralelismo

Paralelismo na supercomputação refere-se à capacidade de executar tarefas computacionais de forma simultânea, dividindo-as em várias partes menores que podem ser processadas em paralelo por múltiplos processadores ou núcleos de processamento.

O paralelismo é utilizado na supercomputação devido à necessidade de processar grandes volumes de dados e realizar cálculos complexos em um tempo razoável. Ele oferece benefícios significativos em termos de desempenho e eficiência, permitindo que várias tarefas sejam executadas ao mesmo tempo, reduzindo o tempo total de processamento.

## Tipos de paralelismo

Existem diferentes formas de paralelismo na computação:

1 - __Paralelismo de tarefa:__ várias tarefas independentes são executadas simultaneamente em diferentes processadores. Cada processador recebe uma tarefa e as executa de forma paralela, aproveitando ao máximo os recursos disponíveis.

2 - __Paralelismo de dados:__ os dados são divididos em partes menores e processados simultaneamente em diferentes processadores. Cada processador manipula uma parte dos dados e, em seguida, os resultados são combinados para obter o resultado final.


## Técnicas exploradas

Neste projeto foi feito uso da alta demanda computacional da heuristica exaustiva para estudar como diferentes técnicas de paralelismo funcionam. 

- __[OpenMP](OpenMP.md):__  OpenMP (Open Multi-Processing) é uma API amplamente utilizada para a programação paralela. O OpenMP permite adicionar diretivas para indicar as regiões que podem ser executadas em paralelo. Essas regiões são chamadas de "regiões paralelas" e são executadas por múltiplas threads simultaneamente, compartilhando a mesma memória.
- __[GPU](GPU.md):__  O paralelismo em GPU (Graphics Processing Unit) refere-se à capacidade de executar múltiplas tarefas de forma simultânea em uma unidade de processamento gráfico. As GPUs são projetadas para lidar com grandes volumes de dados e realizar cálculos intensivos de forma eficiente.
- __MPI:__ MPI (Message Passing Interface) é uma biblioteca para programação paralela em sistemas distribuídos. Ela fornece um conjunto de funções, rotinas e diretrizes que permitem a comunicação e sincronização entre processos executando em diferentes nós de um sistema distribuído.

## Metodologia


Para comparar a eficiência de cada método de paralelismo, registramos o número de combinações que cada técnica foi capaz de processar em um período de 30 segundos, variando a quantidade de filmes como entrada.
