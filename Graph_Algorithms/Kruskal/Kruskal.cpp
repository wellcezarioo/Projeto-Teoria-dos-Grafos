#include <iostream>
#include <fstream>
#include <cstring>
#include <queue>
#include <vector>


using namespace std;

// aresta comum do grafo com <peso, destino>
typedef pair<int, int> aresta;

// essa aresta é apenas para saber a origem da aresta <origem, aresta>
typedef pair<int, aresta> aresta_Kruskal;

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

        void add_v(){
            Qntd_V++;
        }
        
};

void help(){
    cout << "-h : mostra o help\n" 
         << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n"
         << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada \n"
         << "-s : mostra a solução" << endl;
}

int find(vector <int> & parent, int x){
    if(parent[x] != x)
        parent[x] = find(parent, parent[x]);
    return parent[x];
}

void union_by_rank(vector <int> & parent, vector <int> & rank, int x, int y){
    int rootx = find(parent, x);
    int rooty = find(parent, y);

    if(rootx != rooty){
        if(rank[rootx] > rank[rooty]) parent[rooty] = rootx;
        else if(rank[rootx] < rank[rooty]) parent[rootx] = rooty;
        else {
            parent[rooty] = rootx;
            rank[rootx] += 1;
        }
    }
}

void Kruskal(Grafo& g, Grafo& agm) {
    
    int vertices = g.get_qntd_V();

    std::priority_queue<aresta_Kruskal, vector<aresta_Kruskal>, greater<aresta_Kruskal>> pq;
    vector<int> parent(vertices), rank(vertices, 0);

    // Inicializa cada nó como seu próprio pai (Union-Find)
    for (int i = 0; i < vertices; i++) {
        parent[i] = i;
    }

    // Adiciona todas as arestas na fila de prioridade
    for (int v = 0; v < vertices; v++) {
        
        for (const auto & vi : g.get_adj(v)) {
            int peso = vi.first;
            int u = vi.second;
            if (v < u) { // Evita duplicação ao considerar arestas bidirecionais
                pq.push({peso, {v, u}});
            }
        }
    }

    // Processa arestas em ordem crescente de peso
    while (!pq.empty()) {
        auto [peso, vi] = pq.top();
        pq.pop();

        int origem = vi.first;
        int destino = vi.second;

        // Verifica se a aresta forma um ciclo
        if (find(parent, origem) != find(parent, destino)) {
            // Adiciona a aresta na AGM
            agm.nova_aresta(origem, destino, peso);

            // Une os conjuntos
            union_by_rank(parent, rank, origem, destino);
        }
    }
}


int main(int argc, char * argv[]){
    string entrada_nome = ""; 
    string saida_nome = "";
    bool solucao = false;
    ofstream arquivo_saida;

    int vertices, arestas;

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
        else if(strcmp(argv[i], "-s") == 0){
            solucao = true;
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
    Grafo agm(vertices);
    
    for(int i = 0; i < arestas; i++){
        int V, U, P;
        arquivo_entrada >> V >> U >> P;
        V--, U--;
        g.nova_aresta(V, U, P);
        g.nova_aresta(U, V, P);
    }
    arquivo_entrada.close();
    
    Kruskal(g, agm);

    if(solucao){

        for(int j = 0; j < vertices; j++){
            for(auto vi : agm.get_adj(j)){
                cout << "("<< j + 1 << "," << vi.second + 1 << ") ";
            }
        }
        cout << endl;
    }
    else{
        long int soma = 0;
        
        for(int j = 0; j < vertices; j++){
            for(aresta vi : agm.get_adj(j)){
                soma += vi.first;
            }
        }
        
        cout << soma << endl;
    }

    if (arquivo_saida.is_open()) {
        arquivo_saida.close();
    }
    return 0;
}