#include <iostream>
#include <string.h> 
#include <vector>
#include <algorithm>
#include <stdio.h> 
#include <fstream>

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

    public:
    vector<Aresta> arestas;
    vector<Aresta> arvore; 
    int *pai;
    int *vertices;
    int *rank;
    public:
    Grafo(int N){
        this->N = N;
        pai = new int[N];
        vertices = new int[N];
        rank = new int[N];
    }

    void add_aresta(int novo_v1, int novo_v2, int novo_peso){
        Aresta nova_aresta(novo_v1,novo_v2,novo_peso);
        arestas.push_back(nova_aresta);
    }

    void makeset(int x){
        pai[x] = x;
        rank[x] = 0;
    }

    int find(int x){
        if(pai[x] != x){
            pai[x] = find(pai[x]);
        }
        return pai[x];

    }

    void union_(int x, int y){
        if (rank[x] >= rank[y]){
            pai[y] = x;
            if (rank[x] == rank[y])
                rank[x]++;
        }
        else   
            pai[x] = y;
    }
    
    void getV(){
        int indice_1,indice_2;
        for (int i = 0; i < arestas.size(); i++) 
        {
            indice_1 = arestas[i].returnV1();
            indice_2 = arestas[i].returnV2();
            if (vertices[indice_1] != indice_1){
                vertices[indice_1] = indice_1;
            }
            if (vertices[indice_2] != indice_2){
                vertices[indice_2] = indice_2;
            }
        }
    }

    void kruskal(){  
        getV();
        for (int i = 0; i < N; i++){
            makeset(i);
        }
        sort(arestas.begin(), arestas.end());
        for (int i = 0; i < arestas.size(); i++){
            int rep1 = find(arestas[i].returnV1());
            int rep2 = find(arestas[i].returnV2());
            if (rep1 != rep2){
                arvore.push_back(arestas[i]);
                union_(rep1,rep2);
            }
        }
        printGrafo();
    }

    void printGrafo(){
        int i = 0;
        while(i<arvore.size()){
            cout << "   " << arvore[i].returnV1() << "          " << arvore[i].returnV2() << "          " << arvore[i].weight() << endl; 
            i++;
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
    cout << "\nArvore:\n" << endl;
    cout << "Vertice - vertice - peso entre eles" << endl;
    g.kruskal();
    return 0;
}