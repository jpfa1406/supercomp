#include<iostream>
#include<iomanip>
#include<vector>
#include<fstream>
#include<algorithm>
#include<cstring>
#include<chrono>
#include <random>
#include<boost/random.hpp>

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
    vector<filme> melhor;
    vector<filme> tmp;
    assistir.reserve(24);

    default_random_engine generator (10);
    uniform_real_distribution<double> distribution(0.0, 1.0);

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
    size_t maxFilmes = 0;
    sort(filmes.begin(), filmes.end(), ord_duracao);
    
    chrono::steady_clock::time_point start = chrono::steady_clock::now();
    sort(filmes.begin(), filmes.end(), ord_inicio);
    tmp = filmes;

    for (int t = 0; t < 10; t++){    
        filmes = tmp;
        assistir.clear();
        for (size_t i = 0; i < filmes.size(); i++){
            disponivel = all_of(agenda.begin() + filmes[i].inicio, agenda.begin() + filmes[i].fim, [](bool b){ return b == true; });
            if (categorias[filmes[i].categoria - 1] <= 0){
                disponivel = false;
            }
            if (disponivel){
                int categoria_index = filmes[i].categoria - 1;
                for (int k = filmes[i].inicio; k < filmes[i].fim; k++){
                    agenda[k] = false;
                }
                assistir.push_back(filmes[i]);
                maratona += filmes[i].duracao;
                categorias[categoria_index] -= 1; 
            }  
            disponivel = true; 

            if(distribution(generator) < 0.25){
                uniform_int_distribution<int> distribution(i, filmes.size()-1);
                int p = distribution(generator);
                disponivel = all_of(agenda.begin() + filmes[p].inicio, agenda.begin() + filmes[p].fim, [](bool b){ return b == true; });
                if (categorias[filmes[p].categoria - 1] <= 0){
                    disponivel = false;
                }
                if (disponivel){
                    int categoria_index = filmes[p].categoria - 1;
                    for (int k = filmes[p].inicio; k < filmes[p].fim; k++){
                        agenda[k] = false;
                    }
                    assistir.push_back(filmes[p]);
                    maratona += filmes[p].duracao;
                    categorias[categoria_index] -= 1; 
                }  
                filmes.erase(filmes.begin() + p);
                disponivel = true; 
            }

        }
        if(maxFilmes < assistir.size()){
            maxFilmes = assistir.size();
            melhor = assistir;
        }
        for (int i = 0; i < 24; i++){
            agenda[i] = true;
        }
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << n << ' ' << nCat << ' ' << chrono::duration_cast<chrono::microseconds>(end-start).count() << ' ' << melhor.size() << endl;

    if(argc > 2 && strcmp(argv[2], "-output") == 0){ 
        cout << "Quantidade de filmes:" << melhor.size() << endl;
        //cout << "Tempo para assistir:" << maratona << endl;

        sort(melhor.begin(), melhor.end(), ord_inicio);

        output(melhor);
    }

    ofstream outFile;
    outFile.open("outputs/aleatorio/out_" + to_string(n) + "_" + to_string(nCat) + ".txt");
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
        for(int j = 0; j < assistir[i].duracao + 1; j++){
            cout << "\u25A0";
            cout << "\u25A0";
        }
        cout << endl;
    }

}