# OpenMP

## Definição

OpenMP (Open Multi-Processing) é uma API amplamente utilizada para a programação paralela. O OpenMP permite adicionar diretivas para indicar as regiões que podem ser executadas em paralelo. Essas regiões são chamadas de "regiões paralelas" e são executadas por múltiplas threads simultaneamente, compartilhando a mesma memória.

## Principais recusos

1 - __Diretivas:__ são comandos especiais inseridos no código-fonte para indicar as regiões paralelas. As diretivas OpenMP são precedidas por "#pragma omp" e fornecem instruções para o compilador.

2 - __Cláusulas:__ fornecem informações adicionais sobre como a região paralela deve ser executada. Por exemplo, a cláusula "num_threads" especifica o número de threads a serem usadas na região paralela.

4 - __Escopo de variáveis:__ compartilhamento de variáveis entre as threads. Variáveis declaradas fora das regiões paralelas são compartilhadas, enquanto variáveis declaradas dentro de uma região paralela são privadas e têm uma cópia para cada thread.

5 - __Sincronização:__ mecanismos para sincronizar as threads, como as diretivas "barrier", que aguarda todas as threads atingirem um determinado ponto de sincronização, e "critical", que permite que apenas uma thread execute uma seção crítica por vez.


## Implementação
``` cpp
#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<chrono>
#include<math.h>
#include<omp.h>

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
    agenda.reserve(24);

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

    int n_threads= omp_get_max_threads();
    const long long unsigned int slent = pow(2, min(int (filmes.size()), 50));
    vector<int> melhores;
    vector<int> tested(n_threads, 0);
    melhores.resize(n_threads);


    #pragma omp parallel
    {
        int melhor;
        #pragma omp for
        for (long long unsigned int i = 0; i < slent; i++) {
            for (int i = 0; i < 24; i++){
                agenda[i] = true;
            }

            int added = 0;
            for (size_t j = 0; j < filmes.size(); j++){
                if(added > 24 || added < 0) continue;
                if ((i & int(pow(2, j)))) {
                    disponivel = all_of(agenda.begin() + filmes[j].inicio, agenda.begin() + filmes[j].fim, [](bool b){ return b == true; });
                    if (categorias[filmes[j].categoria - 1] <= 0){
                        disponivel = false;
                    }
                    if (disponivel){
                        for (int k = filmes[j].inicio; k < filmes[j].fim; k++){
                            agenda[k] = false;
                        }
                    //assistir.push_back(filmes[j]);
                    maratona += filmes[j].duracao;
                    categorias[filmes[j].categoria - 1] = categorias[filmes[j].categoria - 1] - 1;  
                    }  
                    disponivel = true; 
                    added++;
                }
            }

            chrono::steady_clock::time_point end = chrono::steady_clock::now();

            tested[omp_get_thread_num()]++;
            if(chrono::duration_cast<chrono::seconds>(end-start).count() > 30) {
                #pragma omp critical
                {
                    int sum = 0;
                    for (size_t i = 0; i < n_threads; i++) {
                        sum += tested[i];
                    }
                    cout << 30 << 'x' << slent << 'x' << sum;
                    exit(0);
                }
            }
            if(added <= 24 && added > 0) {
                if(added > melhor) {
                    melhor = added;
                    melhores[omp_get_thread_num()] = melhor;
                }
            }
        }
    }

    int melhor = 0;
    for (size_t i = 0; i < n_threads; i++) {
        if(melhores[i] > melhor) {
        melhor = melhores[i];
        }
    }
    
    int sum = 0;
    for (size_t i = 0; i < n_threads; i++) {
       sum += tested[i];
    }
    cout << 30 << 'x' << slent << 'x' << sum;
    exit(0);

    return 0;
}
```