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

```cpp
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

```
--------------------------------------------------------------------------------
-- User-annotated source: projetoGuloso.cpp
--------------------------------------------------------------------------------
Ir      

-- line 18 ----------------------------------------
      .  
      .  
      .  
      .  bool ord_duracao(filme a, filme b);
      .  bool ord_inicio(filme a, filme b);
      .  void output(vector<filme> assistir);
      .  
      .  
     14  int main(int argc, char *argv[]){
      .  
      5      ifstream inFile;
  6,210  => ???:0x000000000010a390 (1x)
    778  => ???:0x000000000010a270 (1x)
      1      string fileName = argv[1]; 
      .      int n;
      .      int nCat;
      .      int cat;
      .  
      .      vector<int> categorias;
      .      vector<bool> agenda;
      .      vector<filme> filmes;
      .      vector<filme> assistir;
      .      assistir.reserve(24);
      .  
     11      inFile.open("inputs/" + fileName + ".txt");
  6,651  => ???:0x000000000010a330 (1x)
    101  => /usr/include/c++/9/bits/basic_string.h:std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&&, char const*) (1x)
      4      if (!inFile) {
      .          cout << "Unable to open file";
      .          exit(1); // terminate with error
      .      }
      .  
      3      inFile >> n;
  6,007  => ???:0x000000000010a2e0 (1x)
      3      inFile >> nCat;
    405  => ???:0x000000000010a2e0 (1x)
      .  
     23      for (int i = 0; i < nCat; i++){
     15          inFile >> cat;
  2,187  => ???:0x000000000010a2e0 (5x)
      .          categorias.push_back(cat);
      .      }
      .  
     48      for (int i = 0; i < 24; i++){
      .          agenda.push_back(true);
      .      }
      .  
 56,030      for(int i = 0; i < n; i++){
      .          filme k;
      .          int inicio, fim, categoria;
 30,000          inFile >> inicio;
4,362,922  => ???:0x000000000010a2e0 (10,000x)
 30,001          inFile >> fim;
4,361,274  => ???:0x000000000010a2e0 (10,000x)
 30,000          inFile >> categoria;
4,050,376  => ???:0x000000000010a2e0 (10,000x)
 40,000          if(fim > inicio){
  8,690              k.fim = fim;
  8,690              k.inicio = inicio;
 17,380              k.duracao = k.fim - k.inicio;
 17,380              k.categoria = categoria;
 17,380              k.id = i + 3;
      .              filmes.push_back(k);
      .          }        
      .      }
      .  
      .      bool disponivel = true;
      .      int maratona = 0;
      .      
      2      chrono::steady_clock::time_point start = chrono::steady_clock::now();
    937  => ???:0x000000000010a3e0 (1x)
      .      sort(filmes.begin(), filmes.end(), ord_inicio);
      .  
 26,076      for (size_t i = 0; i < filmes.size(); i++){
 52,140          disponivel = all_of(agenda.begin() + filmes[i].inicio, agenda.begin() + filmes[i].fim, [](bool b){ return b == true; });
     70          if (categorias[filmes[i].categoria - 1] <= 0){
      .              disponivel = false;
      .          }
      .          if (disponivel){
    192              for (int k = filmes[i].inicio; k < filmes[i].fim; k++){
      .                  agenda[k] = false;
      .              }
      .              assistir.push_back(filmes[i]);
     20              maratona += filmes[i].duracao;
     50              categorias[filmes[i].categoria - 1] = categorias[filmes[i].categoria - 1] - 1;  
      .          }  
      .          disponivel = true; 
      .      }
      .      
      2      chrono::steady_clock::time_point end = chrono::steady_clock::now();
     40  => ???:0x000000000010a3e0 (1x)
      .      //cout << chrono::duration_cast<chrono::microseconds>(end-start).count() << endl;
      .  
      7      cout << n << ' ' << nCat << ' ' << chrono::duration_cast<chrono::microseconds>(end-start).count() << ' ' << assistir.size() << endl;
  8,039  => ???:0x000000000010a450 (2x)
      .  
      2      if(argc > 2 && strcmp(argv[2], "-output") == 0){  
      .          cout << "Quantidade de filmes:" << assistir.size() << endl;
      .          cout << "Tempo para assistir:" << maratona << endl;
      .  
      .          sort(assistir.begin(), assistir.end(), ord_inicio);
      .  
      .          output(assistir);
      .      }
      .  
      4      ofstream outFile;
  9,244  => ???:0x000000000010a3f0 (1x)
  2,424  => ???:0x000000000010a440 (1x)
     14      outFile.open("outputs/guloso/out_" + to_string(n) + "_" + to_string(nCat) + ".txt");
    935  => ???:0x000000000010a2b0 (1x)
    191  => /usr/include/c++/9/bits/basic_string.h:std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > std::operator+<char, std::char_traits<char>, std::allocator<char> >(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >&&, char const*) (2x)
      2      if (!outFile) {
      .          cout << "Unable to open file";
      .          exit(1); // terminate with error
      .      }
      .  
      8      outFile <<  n << ' ' << nCat << ' ' << chrono::duration_cast<chrono::microseconds>(end-start).count() << ' ' << assistir.size() << endl;
  1,817  => ???:0x000000000010a450 (2x)
      .  
      .      return 0;
     12  }
      .  
      .  bool ord_duracao(filme a, filme b){
      .      return a.duracao < b.duracao;
      .  }
      .  
 98,456  bool ord_inicio(filme a, filme b){
295,368      return a.inicio < b.inicio;
 98,456  }
      .  
      .  void output(vector<filme> assistir){
      .      for (int i = 0; i < 24; i++){
      .          cout << setfill('0') << setw(2) << i; 
      .          cout << " - ";
      .      }
      .  
      .      cout << endl;
-- line 136 ----------------------------------------
-- line 170 ----------------------------------------
      .              cout << "\u25A0";
      .          }
      .          //cout << "\033[0m";
      .          // 
      .          //cout << assistir[i].fim;
      .          cout << endl;
      .      }
      .  
      3  }
--------------------------------------------------------------------------------
Ir      
--------------------------------------------------------------------------------
826,562  events annotated

```

## Resultados

![image info](img/gulosa/img1.png)  

> Representação geral da performace

![image info](img/gulosa/img2.png)  