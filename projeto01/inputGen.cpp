#include <chrono>
#include <random>
#include <fstream>
#include <string>
#include <boost/random.hpp>

using namespace std;

int generateFile(string fileName, int nFilme, int nCategoria) {

    ofstream inputFile;
    inputFile.open(("inputs/in" + fileName + ".txt"));
    inputFile << nFilme << " " << nCategoria << endl;

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator (seed);

    // Definindo distribuição normal com média de 3 e desvio padrão de 1
    normal_distribution<double> distribution_dif(3, 1.0);

    uniform_int_distribution<int> distribution_hr(0, 23);
    uniform_int_distribution<int> distribution_max(1, 24);
    uniform_int_distribution<int> distribution_cat(1, nCategoria);

    vector<int> maxFilmes(nCategoria); // Vetor para armazenar o máximo de filmes por categoria
    for (int i = 0; i < nCategoria; i++) {
        maxFilmes[i] = distribution_max(generator); // Gerando o máximo de filmes para cada categoria
        inputFile << maxFilmes[i] << " "; // Escrevendo o valor no arquivo de entrada
    }
    inputFile << endl;

    for (int i = 0; i < nFilme; i++) {
        int hora_inicio = distribution_hr(generator);
        double dif_media = distribution_dif(generator);
        int hora_fim = ((int)hora_inicio + (int)round(dif_media)) % 24;
        int categoria = distribution_cat(generator);

        inputFile << hora_inicio << " " << hora_fim << " " << categoria << endl;
    }


    inputFile.close();
    return 0;
}

int main(){
    int nFilme = 10000;
    int nCategoria = 1;
    int arq = 1;

    for (int i = 0; i < 20; i++){
        for (int j  = 0; j < 6; j++){
            generateFile(("_" + to_string(nFilme) + "_" + to_string(nCategoria)), nFilme, nCategoria);
            nCategoria++;
            arq++;
        }
        nCategoria = 1;
        nFilme = nFilme + 1000;
    }
    
    
    return 0;
}