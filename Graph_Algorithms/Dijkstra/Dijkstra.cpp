#include <iostream>
#include <queue>
#include <climits>
#include <vector>
#include <cstring>
#include <fstream>

using namespace std;

typedef pair<int, int> aresta;

class Grafo {
    private:
        int Qntd_V; // quantidade de vertices do grafo
        vector < vector < aresta >> adj; // vetor dinamico de adjacencia

    public:
        Grafo(int Vertices) : Qntd_V(Vertices), adj(Vertices) {};

        void nova_aresta(int V, int U, int peso) {
            adj[V].push_back({peso, U});
        }       
        
        int get_qntd_V() const {
            return this->Qntd_V;
        }

        const vector <aresta> & get_adj(int V) const {
            return adj[V];
        }
        
};

void Dijkstra(Grafo & g, vector <int> & dist, int inicial){
    
    dist[inicial] = 0;

    priority_queue < aresta, std::vector <aresta>, std::greater <aresta> > pq;
    pq.push({0, inicial});

    while(!pq.empty()){
        int d = pq.top().first; 
        int v = pq.top().second; 
        pq.pop();

        if(d > dist[v]) continue;

        for(auto vizinho : g.get_adj(v)){
            int u = vizinho.second;
            int peso = vizinho.first;

            if(dist[v] + peso < dist[u]){
                dist[u] = dist[v] + peso;
                pq.push({dist[u], u});
            }
        }
    }

}

void help(){
    cout << "-h : mostra o help\n" 
         << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n"
         << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada \n"
         << "-i : vértice inicial" << endl;
}

int main(int argc, char * argv[]){

    string entrada_nome = ""; 
    string saida_nome = "";
    ofstream arquivo_saida;

    int inicial = 0, vertices, arestas;

    for(int i = 1; i < argc; i++){
        if(strcmp(argv[i], "-o") == 0){
            saida_nome = argv[++i];
            arquivo_saida.open(saida_nome);
            if (!arquivo_saida.is_open()) {
                cerr << "Erro ao abrir o arquivo de saída: " << saida_nome << endl;
                return 1;
            }

            // Redireciona cout para o arquivo
            cout.rdbuf(arquivo_saida.rdbuf());
        }
        else if(strcmp(argv[i], "-f") == 0){
            entrada_nome = argv[++i];
        }
        else if(strcmp(argv[i], "-i") == 0){
            inicial = stoi(argv[++i]) - 1;
        }
        else if(strcmp(argv[i], "-h") == 0){
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
    Grafo g(vertices);

    vector <int> dist(vertices, INT_MAX);
    for(int i = 0; i < arestas; i++){
        int V, U, P;
        arquivo_entrada >> V >> U >> P;
        V--, U--;
        g.nova_aresta(V, U, P);
        g.nova_aresta(U, V, P);
    }
    arquivo_entrada.close();
    
    Dijkstra(g, dist, inicial);

    for(int j = 0; j < vertices; j++){
        cout << j + 1 << ':';
        cout << (dist[j] == INT_MAX ? -1 : dist[j]) << ' ';
    }
    cout << std::endl;

    if (arquivo_saida.is_open()) {
        arquivo_saida.close();
    }
    return 0;
}