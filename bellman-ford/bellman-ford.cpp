#include <iostream>
#include <string.h> 
#include <vector>
#include <algorithm>
#include <stdio.h> 
#include <fstream>

#define infinito std::numeric_limits<int>::max()

using namespace std;

class Aresta{
    int vertice1, vertice2, peso;

    public:
    Aresta(int v1, int v2, int p){
        vertice1 = v1;
        vertice2 = v2;
        this->peso = p;
    }
    int returnV1(){
        return vertice1;
    }
    int returnV2(){
        return vertice2;
    }
    int weight(){
        return peso;
    }
    bool operator < (const Aresta& edge) const{
        return (peso < edge.peso);
    }
};

class Grafo{
    int N;
    vector<Aresta> arestas;
    int *distancias;

    public:
    Grafo(int N){
        this->N = N;
    }

    void add_aresta(int novo_v1, int novo_v2, int novo_peso){
        Aresta nova_aresta(novo_v1,novo_v2,novo_peso);
        arestas.push_back(nova_aresta);
    }

    void update(int u, int v, int peso, int max){
        if (distancias[u] != max && distancias[u]+peso < distancias[v]){
            distancias[v] = distancias[u] + peso;
        }
    }

    int verifica(){
        int u,v,peso;
        for (int i = 0; i < N - 1; i++){
            u = arestas[i].returnV1();  //primeiro vértice da aresta (u)
            v = arestas[i].returnV2();  //segundo vertice da aresta (v)
            peso = arestas[i].weight(); //peso da aresta
            if (distancias[u] + peso < distancias[v]){
                return 1;
            }
        }
        return 0;
    }   

    void bellman_ford(){
        int num_max = infinito;
        int tamanho = arestas.size();
        int u,v,peso;
        distancias = new int[tamanho];
        int inicio = arestas[0].returnV1();
        for (int i = 0; i < N; i++){
            distancias[i] = num_max;
        }
        distancias[inicio] = 0;
        for (int i = 0; i < N - 1; i++){
            for (int j = 0; j < arestas.size(); j++){
                u = arestas[j].returnV1();
                v = arestas[j].returnV2();
                peso = arestas[j].weight();
                update(u,v,peso,num_max);
            }
        }
        if (verifica()) 
            return;
        else printGrafo();
    }

    void printGrafo(){
        cout << "\n\nDistancia do vertice atual ao inicial:\n" << endl;
        for (int i = 0; i < N; i++){
            cout << "Vertice: "<< i << " -> Distancia: " << distancias[i] << endl;  
        }
    }
};

int main(int argc, char *argv[]){
    int vertices, arestas, v1, v2, peso;
    ifstream entrada("entrada.in");
    entrada >> vertices >> arestas;
    Grafo g(vertices);
    for ( ; arestas > 0; arestas--){
        entrada >> v1 >> v2 >> peso;
        g.add_aresta(v1,v2,peso);
    }
    g.bellman_ford();
    return 0;
}