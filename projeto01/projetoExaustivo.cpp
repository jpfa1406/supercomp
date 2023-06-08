#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<chrono>
#include<math.h>

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
    int tested = 0;
    
    chrono::steady_clock::time_point start = chrono::steady_clock::now();

    const long long unsigned int slent = pow(2, min(int (filmes.size()), 50));
    int melhor = 0;

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
                assistir.push_back(filmes[j]);
                maratona += filmes[j].duracao;
                categorias[filmes[j].categoria - 1] = categorias[filmes[j].categoria - 1] - 1;  
                }  
                disponivel = true; 
                added++;
            }
        }

        chrono::steady_clock::time_point end = chrono::steady_clock::now();

        tested++;
        if(chrono::duration_cast<chrono::microseconds>(end-start).count() > 30000000) {
            cout << 30 << 'x' << slent << 'x' << tested;
            exit(0);
        }
        if(added <= 24 && added > 0) {
            if(added > melhor) {
                melhor = added;
            }
        }
    }
    cout << 30 << 'x' << slent << 'x' << tested;

    return 0;
}

