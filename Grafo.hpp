#ifndef GRAFO_HPP_INCLUDED
#define GRAFO_HPP_INCLUDED

#include "ListaLigada.hpp"
#include "Fila.hpp"

typedef int Vertice;
typedef float Peso;
enum Cor {Branco, Cinza, Preto};
enum Status {Amigo, Inimigo};

//Grafo por lista de adjacências
class Grafo_LA{
public:
    Grafo_LA(int);
    ~Grafo_LA();
    void inserirAresta(Vertice, Vertice, Peso = 0);
    void inserirArestaDirecionada(Vertice, Vertice, Peso = 0);
    void removerAresta(Vertice, Vertice);
    void mostrar();
    void reinicializar(int);
    ListaLigada<Vertice>* getAdj();
    int** getPesos() const;
    int getTamanho() const;
    int getNumArestas() const;
    Status* getStatus() const;
    void marcarInimigo(Vertice);

    friend void DFS(Grafo_LA&);
    friend void DSF_VISITA(Grafo_LA&);
private:
    Status* status;
    int** pesos;
    void inicializar(int);
    void destruir();
    ListaLigada<Vertice>* adj;
    int n, m; // n° de vertices e arestas
};


//para grafo LA
class BuscaEmProfundidade{
public:
    BuscaEmProfundidade();
    ~BuscaEmProfundidade();
    void DFS(Grafo_LA&);
    void DFS_VISITA(Grafo_LA&, int);
    float getSomatorio() const;
    ListaLigada<Vertice> ordemTopologica; //apenas para grafos direcionados acicliclos
private:
    Cor* cor;
    float somatorio;
    int* predecessorVertice;
    int* tempoEntrada;
    int* tempoSaida;
    int tempo;
};



class BuscaEmLargura{
public:
    BuscaEmLargura();
    ~BuscaEmLargura();
    void BFS(Grafo_LA&, Vertice);
    int* getDistancia() const;
    int* getPredecessores() const;
private:
    Cor* cor;
    int* predecessorVertice;
    int* distancia;
    int distAtual;
    Fila<Vertice> fila;
};


#endif // GRAFO_HPP_INCLUDED
