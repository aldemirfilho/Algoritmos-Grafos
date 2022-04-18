#include <iostream>
#include <string.h> 
#include <vector>
#include <algorithm>
#include <stdio.h> 
#include <fstream>
#include <queue>

#define infinito std::numeric_limits<int>::max()

using namespace std;
typedef pair<int, int> Aresta;

void add_aresta(vector<Aresta> grafo[], int inicial, int final, int peso){
	grafo[inicial].push_back(make_pair(final, peso)); // Formação de aresta sem direção definida
	grafo[final].push_back(make_pair(inicial, peso));
}

void prim(vector<Aresta> grafo[], int vertices){
	priority_queue<Aresta, vector<Aresta>, greater<Aresta>> pq;
	vector<int> custo(vertices, infinito);
	vector<int> AGM(vertices, -1);
	vector<bool> marcado(vertices, false);
	
	printf("Comecando com V0 = 0\n");
	custo[0] = 0;
	pq.push(make_pair(0, 0));

	while(!pq.empty()){
		int vertice =  pq.top().second;
		pq.pop();
		marcado[vertice] = true;
		for(auto item: grafo[vertice]){
			int u = item.first;
			int peso = item.second;
			if(marcado[u] == false && custo[u] > peso){
				custo[u] = peso;
				pq.push(make_pair(custo[u], u));
				AGM[u] = vertice;
			}
		}
	}
	printf("Arvore Geradora Minima:\n\n");
	for (int i = 1; i < vertices; ++i) 
        printf("%d -> %d\n", AGM[i], i);
}

int main(){
	int vertices, arestas, i, j, pesos;
    ifstream entrada("prim.in");
    entrada >> vertices >> arestas;
    vector<Aresta> grafo[vertices];
    printf("\nAo criar grafo...\n\n\n");
	for( ; arestas > 0; arestas--){
    	entrada >> i >> j >> pesos;
    	add_aresta(grafo, i, j, pesos);
    }
    printf("Aplicando Prim...\n\n");
    prim(grafo, vertices); 
    return 0; 
}