#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <queue>
#include <algorithm>

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

        void add_v(){
            Qntd_V++;
        }
        
};



void Prim(Grafo &g, Grafo &agm, int inicial) {
    
    // Priority queue para armazenar arestas com base no menor peso
    // Armazena pares na forma: {peso, {origem, destino}}
    priority_queue<pair<int, aresta>, vector<pair<int, aresta>>, greater<pair<int, aresta>>> pq;
    
    int Qntd_V = g.get_qntd_V();
    vector<bool> esta_na_agm(Qntd_V, false); // Marca os vértices que já estão na AGM

    // Adiciona todas as arestas do vértice inicial à fila de prioridade
    esta_na_agm[inicial] = true;
    for (auto vi : g.get_adj(inicial)) {
        pq.push({vi.first, {inicial, vi.second}}); // {peso, {origem, destino}}
    }

    int n = 1; // Número de vértices na AGM

    // Enquanto a MST não incluir todos os vértices
    while (n < Qntd_V && !pq.empty()) {

        // Obtém a menor aresta da fila de prioridade, aresta_atual e peso são criados
        // apenas para melhorar a legibilidade do codigo, pois aresta_atual quase não é usada por mim aqui
        auto [peso, aresta_atual] = pq.top();
        pq.pop();
        
        int origem = aresta_atual.first;
        int destino = aresta_atual.second;

        // Se o vértice de destino já estiver na AGM, ignore
        if (esta_na_agm[destino]) continue;

        // Caso contrário, adiciona a aresta à AGM
        agm.nova_aresta(origem, destino, peso);

        esta_na_agm[destino] = true; // Marca o vértice como incluído na AGM
        n++;

        // Adiciona todas as arestas do novo vértice `destino` à fila de prioridade
        for (auto vi : g.get_adj(destino)) {
            if (!esta_na_agm[vi.second]) { // Apenas arestas para vértices fora da AGM
                pq.push({vi.first, {destino, vi.second}});
            }
        }
    }
}


void help(){
    cout << "-h : mostra o help\n" 
         << "-o <arquivo> : redireciona a saida para o ‘‘arquivo’’\n"
         << "-f <arquivo> : indica o ‘‘arquivo’’ que contém o grafo de entrada \n"
         << "-s : mostra a solução"
         << "-i : vértice inicial" << endl;
}

int main(int argc, char * argv[]){
    string entrada_nome = ""; 
    string saida_nome = "";
    bool solucao = false;
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

    Prim(g, agm, inicial);
    
    if(solucao){

        for(int j = 0; j < vertices; j++){
            for(aresta vi : agm.get_adj(j)){
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