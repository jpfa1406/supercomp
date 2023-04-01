# Gulosa

## Definição

Heurística gulosa é um algoritmo de busca (greedy) que segue um processo unico de seleção em cada passo.

O algoritmo possui uma regra de decisão unica e a aplica a cada passo, seleciona a opção valida que aparecer primeiro, sem levar em consideração o impacto de longo prazo dessa escolha. Dessa forma, a heurística gulosa busca maximizar uma função objetivo ou minimizar um custo de forma incremental, esperando que a soma das escolhas locais leve a uma solução aceitável, uma vez que pode terminar antes de observar diverças opções.

## Vantagens

- __Eficiência:__ as heurísticas gulosas geralmente são algoritmos de baixa complexidade computacional.
- __Facilidade de implementação:__ em comparação com outras técnicas de otimização, as heurísticas gulosas são relativamente fáceis de implementar.

## Desvantagens

- __Soluções sub-ótimas:__ a baixa exploração favorece a melhor opção local, ignora opções que parecem menos vantajosas no momento, mas que poderiam levar a uma solução global melhor.

## Implementação

```
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<chrono>

using namespace std;

struct filme{
    int inicio;
    int fim;
    int categoria;
    int duracao;
    int id;
};



bool ord_duracao(filme a, filme b);
bool ord_inicio(filme a, filme b);
void output(vector<filme> assistir);


int main(int argc, char *argv[]){

    ifstream inFile;
    string fileName = argv[1]; 
    int n;
    int nCat;
    int cat;

    vector<int> categorias;
    vector<bool> agenda;
    vector<filme> filmes;
    vector<filme> assistir;
    assistir.reserve(24);

    inFile.open("inputs/" + fileName + ".txt");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    inFile >> n;
    inFile >> nCat;

    for (int i = 0; i < nCat; i++){
        inFile >> cat;
        categorias.push_back(cat);
    }

    for (int i = 0; i < 24; i++){
        agenda.push_back(true);
    }

    for(int i = 0; i < n; i++){
        filme k;
        int inicio, fim, categoria;
        inFile >> inicio;
        inFile >> fim;
        inFile >> categoria;
        if(fim > inicio){
            k.fim = fim;
            k.inicio = inicio;
            k.duracao = k.fim - k.inicio;
            k.categoria = categoria;
            k.id = i + 3;
            filmes.push_back(k);
        }        
    }

    bool disponivel = true;
    int maratona = 0;
    
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    sort(filmes.begin(), filmes.end(), ord_inicio);

    for (size_t i = 0; i < filmes.size(); i++){
        disponivel = all_of(agenda.begin() + filmes[i].inicio, agenda.begin() + filmes[i].fim, [](bool b){ return b == true; });
        if (categorias[filmes[i].categoria - 1] <= 0){
            disponivel = false;
        }
        if (disponivel){
            for (int k = filmes[i].inicio; k < filmes[i].fim; k++){
                agenda[k] = false;
            }
            assistir.push_back(filmes[i]);
            maratona += filmes[i].duracao;
            categorias[filmes[i].categoria - 1] = categorias[filmes[i].categoria - 1] - 1;  
        }  
        disponivel = true; 
    }
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    //cout << chrono::duration_cast<chrono::microseconds>(end-start).count() << endl;

    cout << n << ' ' << nCat << ' ' << chrono::duration_cast<chrono::microseconds>(end-start).count() << ' ' << assistir.size() << endl;

    if(argc > 2 && strcmp(argv[2], "-output") == 0){  
        cout << "Quantidade de filmes:" << assistir.size() << endl;
        cout << "Tempo para assistir:" << maratona << endl;

        sort(assistir.begin(), assistir.end(), ord_inicio);

        output(assistir);
    }

    ofstream outFile;
    outFile.open("outputs/guloso/out_" + to_string(n) + "_" + to_string(nCat) + ".txt");
    if (!outFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }

    outFile <<  n << ' ' << nCat << ' ' << chrono::duration_cast<chrono::microseconds>(end-start).count() << ' ' << assistir.size() << endl;

    return 0;
}

bool ord_duracao(filme a, filme b){
    return a.duracao < b.duracao;
}

bool ord_inicio(filme a, filme b){
    return a.inicio < b.inicio;
}

void output(vector<filme> assistir){
    for (int i = 0; i < 24; i++){
        cout << setfill('0') << setw(2) << i; 
        cout << " - ";
    }

    cout << endl;
    
    for (size_t i = 0; i < assistir.size(); i++){
        for (int j = 0; j < assistir[i].inicio; j++){
           cout << "     ";
        }
        
        //cout << assistir[i].inicio;
        if(assistir[i].categoria == 1){
            cout << "\033[1;31m";//vermelho
        }
        else if(assistir[i].categoria == 2){
            cout << "\033[1;32m";//verde
        }
        else if(assistir[i].categoria == 3){
            cout << "\033[1;33m";//azul
        }
        else if(assistir[i].categoria == 4){
            cout << "\033[1;34m";//amarelo
        }
        else if(assistir[i].categoria == 5){
            cout << "\033[1;35m";
        }
        else{
            cout << "\033[1;36m";
        }
        for(int j = 0; j < assistir[i].duracao; j++){
            cout << "\u25A0";
            cout << "\u25A0";
            cout << "\u25A0";
        }
        // 1 - 1, 2 - 2, 3 -3 
        for(int j = 0; j < assistir[i].duracao + 1; j++){
            cout << "\u25A0";
            cout << "\u25A0";
        }
        //cout << "\033[0m";
        // 
        //cout << assistir[i].fim;
        cout << endl;
    }

}
```

## Desempenho



## Resultados

![image info](./projeto01/outputs/gulosa/img1.png)  

> Representação geral da performace

![image info](./projeto01/utputs/gulosa/img2.png)  