#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <climits>


using namespace std;
//detecção de ciclo negativo adicionada!
bool detect_negative_cycle(int vertices, vector<vector<int>> &dist) {
    for (int i = 0; i < vertices; i++) {
        if (dist[i][i] < 0) {
            return true; 
        }
    }
    return false;
}

void floyd_warshall(int vertices, vector<vector<int>> &dist) {
    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if ((dist[i][j] > dist[i][k] + dist[k][j]) && (dist[k][j] != INT_MAX && dist[i][k] != INT_MAX)) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

void help() {
    cout << "-h : mostra o help\n" 
         << "-o <arquivo> : redireciona a saida para o 'arquivo'\n"
         << "-f <arquivo> : indica o 'arquivo' que contem o grafo de entrada\n"
         << "-s : mostra a matriz de caminhos minimos" << endl;
}

int main(int argc, char *argv[]) {
    string entrada_nome = "";
    string saida_nome = "";
    bool solucao = false;
    ofstream arquivo_saida;

    int vertices, arestas;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            saida_nome = argv[++i];
            arquivo_saida.open(saida_nome);
            if (!arquivo_saida.is_open()) {
                cerr << "Erro ao abrir o arquivo de saida: " << saida_nome << endl;
                return 1;
            }

            // Redireciona cout para o arquivo
            cout.rdbuf(arquivo_saida.rdbuf());
        } else if (strcmp(argv[i], "-f") == 0) {
            entrada_nome = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0) {
            solucao = true;
        } else if (strcmp(argv[i], "-h") == 0) {
            help();
            return 0;
        }
    }

    ifstream arquivo_entrada(entrada_nome);
    if (!arquivo_entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada: " << entrada_nome << endl;
        return 1;
    }

    arquivo_entrada >> vertices >> arestas;
    vector<vector<int>> dist(vertices, vector<int>(vertices, INT_MAX));

    // Inicializa a diagonal principal com zero (distancia de um vertice para ele mesmo)
    for (int i = 0; i < vertices; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < arestas; i++) {
        int u, v, p;
        arquivo_entrada >> u >> v >> p;

        dist[--u][--v] = p;
    }

    arquivo_entrada.close();

    floyd_warshall(vertices, dist);
    
    if (detect_negative_cycle(vertices, dist)) {
        cerr << "Erro: Ciclo negativo detectado no grafo." << endl;
        if (arquivo_saida.is_open()) {
            arquivo_saida.close();
        }
        return 1;
    }
    
    if (solucao) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][j] == INT_MAX) {
                    cout << "- ";
                } else {
                    cout << dist[i][j] << " ";
                }
            }
            cout << endl;
        }
    }

    if (arquivo_saida.is_open()) {
        arquivo_saida.close();
    }
    return 0;
}
