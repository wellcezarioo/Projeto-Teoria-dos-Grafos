#include "Dijkstra.hpp"

// metodo construtor, inicalizando qntd_V e adj antes do corpo ser inicializado
// esse metodo é mais eficiente, pois se fossem inicializadas no corpo
// Qntd_v e adj receberiam valores padrão e só depois seriam inicializadas com os
// valores certos, aprendi agora isso
Grafo::Grafo(int Vertices) : Qntd_V(Vertices), adj(Vertices) {}

void Grafo::nova_aresta(int V, int U, int peso){

    // adciona a aresta {U, Peso} ao vetor de adjacencia
    adj[V].push_back({peso, U});
}

// metodo para ler a quantidade de vértices do graafo, usando o conceito de
// encapsulamento, visibilidade e imutabilidade
int Grafo::get_qntd_V() const {
    return this->Qntd_V;
}

const vector <aresta> & Grafo::get_adj(int V) const {
    return adj[V];
}

void Dijkstra(Grafo & g, int inicial){

    // inicializando o vetor de distancias com distancia infinita inicialmente
    int vertices = g.get_qntd_V();
    vector <int> dist(vertices, INT_MAX);
    dist[inicial] = 0;

    // fila de prioridade min-heap
    priority_queue < aresta, vector <aresta>, greater <aresta> > pq;
    pq.push({0, inicial});

    while(not pq.empty()){

        // vertice com a menor distancia até o vertice inicial
        // que esta atualmente na fila

        int v = pq.top().second; // vertice
        int d = pq.top().first; // distancia de v ao vertice inical pela aresta atual

        pq.pop();

        // se ja conhecemos um caminho menor que passa por v, então não consideramos esse
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

    // mostrando as menores distancias do vertice inicial até cada vertice
    for(int i = 0; i < vertices; i++){
        std::cout << i+1 << ':';
        std::cout << (dist[i] == INT_MAX ? -1 : dist[i]) << ' ';
        
    }
    cout << endl;
}
