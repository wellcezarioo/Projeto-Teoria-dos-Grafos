#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <iostream>
#include <queue>
#include <climits>
#include <vector>

typedef pair<int, int> aresta;

class Grafo{
    private:
        int Qntd_V; // quantidade de vertices do grafo
        vector < vector < aresta >> adj; // vetor dinamico de adjacencia

    public:

        // metodo construtor
        Grafo(int Vertices);

        void nova_aresta(int V, int U, int peso);
        
        int get_qntd_V() const;
        const vector <aresta> & get_adj(int V) const;
        
};

void Dijkstra(Grafo & g, int inicial);

#endif // DIJKSTRA_HPP