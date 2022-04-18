#include <iostream>
#include <string.h> 
#include <vector>
#include <algorithm>
#include <stdio.h> 
#include <fstream>
#include <queue>

#define infinito std::numeric_limits<int>::max()

using namespace std;
typedef pair<int, int> Aresta; //Definição de aresta como sendo um par de inteiros

void add_aresta(vector<Aresta> grafo[], int inicial, int final, int peso){
	grafo[inicial].push_back(make_pair(final, peso));
	//forma par de vértices que compoe a aresta orientada
}

void dijkstra(vector<Aresta> grafo[], int vertices){
	priority_queue<Aresta, vector<Aresta>, greater<Aresta>> pq;
	vector<int> dist(vertices, infinito);
	vector<int> previous(vertices, -1);
	vector<bool> marcado(vertices, false);

	printf("Inicio em V0 = 0\n\n");
	dist[0] = 0;
	pq.push(make_pair(0, 0));

	while(!pq.empty()){
		int vertice =  pq.top().second;
		pq.pop();
		marcado[vertice] = true;
		for(auto item: grafo[vertice]){
			int v = item.first;			//segundo vértive da aresta (u, v)
			int peso = item.second;     //peso da aresta
			if(marcado[v] == false && dist[v] > dist[vertice] + peso){
				dist[v] = dist[vertice] + peso; 
				previous[v] = vertice;
				pq.push(make_pair(dist[v], v));
			}
		}
	}
	printf("Arvore de Dijkstra:\n");
	for (int i = 1; i < vertices; ++i) 
        printf("%d -> %d\n", previous[i], i);
}

int main(){
    int vertices, arestas, i, j, pesos;
    ifstream entrada("entrada.in");
    entrada >> vertices >> arestas;
    vector<Aresta> grafo[vertices];
    printf("\nAo criar grafo...\n\n\n");
	for( ; arestas > 0; arestas--){
    	entrada >> i >> j >> pesos;
    	add_aresta(grafo, i, j, pesos);
    }
    printf("Aplicando Dijkstra...\n\n");
    dijkstra(grafo, vertices); 
    return 0; 
} 