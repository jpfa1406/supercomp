# Metodologia

Para todas as heurísticas, foram utilizados os mesmos arquivos de entrada, modelo de saída e simplificações gerais, embora possam existir simplificações ou limitações específicas descritas em sua implementação.

## Inputs

Utilizou-se um gerador de entradas que criou diversos arquivos, variando os parâmetros, quantidade de filmes, categorias e limite de filmes por categoria, além de gerar filmes aleatórios (com horário de início, fim e categoria).

#### Especificações:

- Quantidade de filmes: 10 - 100000000
- Quantidade de categorias: 1 - 9
- Limite de filme: 
- Duração dos filmes: 

#### Ex:

```
10 4
1 3 1 2  
11 13 3  
14 15 3  
10 16 2  
10 14 1  
11 17 2  
11 14 3  
13 15 3  
14 15 1  
12 16 4  
```

## Simplificações do problema

Para simplificar o problema, não foi imposto um mínimo de filmes por categoria, e também não foram considerados filmes que terminassem no dia seguinte, uma vez que isso aumentaria significativamente a complexidade do desenvolvimento das heurísticas.

## Outputs

Para cada arquivo de entrada, gerou-se um arquivo de saída contendo informações sobre o input recebido e métricas de desempenho no modelo: quantidade de filmes, quantidade de categorias, tempo de processamento e tempo de exibição. O __tempo de processamento__ refere-se ao tempo em microssegundos que o algoritmo levou para gerar o output, enquanto o __tempo de exibição__ é a soma da duração de todos os filmes assistidos.

#### Ex:

```
(1000 6 0002 17)
```
