# Problema

Para estudar e entender as heuriscas foi criado um problema (Maratona de Filmes) para testar.  

## Maratona de Filmes

> Retirado do site da materia

Você quer passar um final de semana assistindo ao máximo de filmes possível, mas há restrições quanto aos horários disponíveis e ao número de títulos que podem ser vistos em cada categoria (comédia, drama, ação, etc).  

**Entrada**: Um inteiro N representando o número de filmes disponíveis para assistir e N trios de inteiros (H[i], F[i], C[i]), representando a hora de início, a hora de fim e a categoria do i-ésimo filme. Além disso, um inteiro M representando o número de categorias e uma lista de M inteiros representando o número máximo de filmes que podem ser assistidos em cada categoria.

**Saída**: Um inteiro representando o número máximo de filmes que podem ser assistidos de acordo com as restrições de horários e número máximo por categoria.  

## Exemplo de de input

Como exemplo, considere o seguinte arquivo input.txt gerado:

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
12 13 4  
```

- a primeira linha indica a quantidade de filmes (10) e categorias(4);  
- a segunda linha indica o máximo de filmes que cada categoria pode ter;  
- da terceira linha em diante, os n filmes, suas respectivas hora de início, hora de término e categoria pertencente.  

