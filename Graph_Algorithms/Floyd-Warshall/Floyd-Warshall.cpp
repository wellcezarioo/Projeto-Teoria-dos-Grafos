#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

//detecção de ciclo negativo
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
                    if(dist[i][k] + dist[k][j] < 0) continue;
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

void help() {
    cout << "-h : mostra o help\n" 
         << "-o <arquivo> : redireciona a saida para o 'arquivo'\n"
         << "-f <arquivo> : indica o 'arquivo' que contem o grafo de entrada\n";
}

int main(int argc, char *argv[]) {
    string entrada_nome = "";
    string saida_nome = "";
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
        } else if (strcmp(argv[i], "-f") == 0) {
            entrada_nome = argv[++i];
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

    if (!arquivo_saida.is_open()) {
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
    } else {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][j] == INT_MAX) {
                    arquivo_saida << "- ";
                } else {
                    arquivo_saida << dist[i][j] << " ";
                }
            }
            arquivo_saida << endl;
        }
    }


    if (arquivo_saida.is_open()) {
        arquivo_saida.close();
    }
    
    return 0;
}
