#include <iostream>
#include <vector>
#include <stack>
#include <fstream>
#include <cstring>

using namespace std;

typedef pair<int, int> aresta;

class Grafo {
    private:
        int Qntd_V;
        vector<vector<int>> adj;

    public:
        Grafo(int Vertices) : Qntd_V(Vertices), adj(Vertices) {}

        void nova_aresta(int V, int U) {
            adj[V].push_back(U);
        }

        int get_qntd_V() const {
            return Qntd_V;
        }

        const vector<int>& get_adj(int V) const {
            return adj[V];
        }

        Grafo get_transposto() const {
            Grafo g_transposto(Qntd_V);
            for (int v = 0; v < Qntd_V; v++) {
                for (int u : adj[v]) {
                    g_transposto.nova_aresta(u, v);
                }
            }
            return g_transposto;
        }
};

void dfs(int v, const Grafo& g, vector<bool>& visitado, stack<int>& pilha) {
    visitado[v] = true;
    for (int u : g.get_adj(v)) {
        if (!visitado[u]) {
            dfs(u, g, visitado, pilha);
        }
    }
    pilha.push(v);
}

void dfs_transposto(int v, const Grafo& g_transposto, vector<bool>& visitado) {
    visitado[v] = true;
    cout << v + 1 << " ";
    for (int u : g_transposto.get_adj(v)) {
        if (!visitado[u]) {
            dfs_transposto(u, g_transposto, visitado);
        }
    }
}

void kosaraju(const Grafo& g) {
    int V = g.get_qntd_V();
    stack<int> pilha;
    vector<bool> visitado(V, false);

    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            dfs(i, g, visitado, pilha);
        }
    }

    Grafo g_transposto = g.get_transposto();
    fill(visitado.begin(), visitado.end(), false);

    while (!pilha.empty()) {
        int v = pilha.top();
        pilha.pop();
        if (!visitado[v]) {
            dfs_transposto(v, g_transposto, visitado);
            cout << "\n";
        }
    }
}

void help() {
    cout << "-h : mostra o help\n"
         << "-o <arquivo> : redireciona a saida para o ''arquivo''\n"
         << "-f <arquivo> : indica o ''arquivo'' que contém o grafo de entrada \n" << endl;
}

int main(int argc, char* argv[]) {
    string entrada_nome = "";
    string saida_nome = "";
    ofstream arquivo_saida;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-o") == 0) {
            saida_nome = argv[++i];
            arquivo_saida.open(saida_nome);
            if (!arquivo_saida.is_open()) {
                cerr << "Erro ao abrir o arquivo de saída: " << saida_nome << endl;
                return 1;
            }
            cout.rdbuf(arquivo_saida.rdbuf());
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

    int vertices, arestas;
    arquivo_entrada >> vertices >> arestas;
    Grafo g(vertices);

    for (int i = 0; i < arestas; i++) {
        int V, U;
        arquivo_entrada >> V >> U;
        V--, U--;
        g.nova_aresta(V, U);
    }
    arquivo_entrada.close();

    kosaraju(g);

    // redireciona o buffer de saida
    // evita a mensagem de segmentation fault (core dumped) no final
    cout.rdbuf(nullptr);

    if (arquivo_saida.is_open()) {
        arquivo_saida.close();
    }

    return 0;
}
