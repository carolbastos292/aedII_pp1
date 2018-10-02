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

//Grafo por matriz de adjacências
class Grafo_MA{
public:
    Grafo_MA(int);
    ~Grafo_MA();
    void inserirAresta(Vertice, Vertice, Peso = 0);
    void removerAresta(Vertice, Vertice);
    void mostrar();
    void reinicializar(int);
    int getTamanho();
    int** getMatriz() const;
    int** getPesos() const;
private:
    void inicializar(int);
    void destruir();
    int n, m;
    int** mat;
    int** pesos;
};

//para grafo LA
class BuscaEmProfundidade{
public:
    BuscaEmProfundidade();
    ~BuscaEmProfundidade();
    void DFS(Grafo_LA&);
    void DFS_VISITA(Grafo_LA&, int);
    ListaLigada<Vertice> ordemTopologica; //apenas para grafos direcionados acicliclos
private:
    Cor* cor;
    int* predecessorVertice;
    int* tempoEntrada;
    int* tempoSaida;
    int tempo;
};

class BuscaEmProfundidade_MA{
public:
    BuscaEmProfundidade_MA();
    ~BuscaEmProfundidade_MA();
    void DFS(Grafo_MA&);
    void DFS_VISITA(Grafo_MA&, int);
    ListaLigada<Vertice> ordemTopologica; //apenas para grafos direcionados acicliclos
private:
    Cor* cor;
    int* predecessorVertice;
    int* tempoEntrada;
    int* tempoSaida;
    int tempo;
};

class BuscaEmLargura{
public:
    BuscaEmLargura();
    ~BuscaEmLargura();
    void BFS(Grafo_LA&, Vertice, Vertice);
    int* getDistancia() const;
private:
    Cor* cor;
    int* predecessorVertice;
    int* distancia;
    int distAtual;
    Fila<Vertice> fila;
};

class BuscaEmLargura_MA{
public:
    BuscaEmLargura_MA();
    ~BuscaEmLargura_MA();
    void BFS(Grafo_MA&, Vertice);
    int* getDistancia() const;
private:
    Cor* cor;
    int* predecessorVertice;
    int* distancia;
    int distAtual;
    Fila<Vertice> fila;

};

class MST{
public:
    MST();
    ~MST();
    void destruir();
    void reinicializar();
    void MST_Prim(Grafo_LA&, Vertice);
    void MST_Kruskal(Grafo_LA&);
    void mostrar(Grafo_LA&);
    void mostrarSomatorio(Grafo_LA&);
private:
    int n;
    int* chave;
    Vertice* pai;
    FilaPrioridades* fila;
};

class MST_MA{
public:
    MST_MA();
    ~MST_MA();
    void destruir();
    void reinicializar();
    void MST_Prim(Grafo_MA&, Vertice);
    void MST_Kruskal(Grafo_MA&);
    void mostrar(Grafo_MA&);
    void mostrarSomatorio(Grafo_MA&);
private:
    int* chave;
    Vertice* pai;
    FilaPrioridades* fila;
};

class Dijkstra{
public:
    Dijkstra();
    ~Dijkstra();
    void menorCaminho(Grafo_LA&, Vertice);
    void relaxa(Vertice, Vertice);
    void mostrarDistancia();
private:
    int raiz;
    int n;
    int** peso;
    int* pai;
    int* distancia;
    FilaPrioridades* fila;
};


#endif // GRAFO_HPP_INCLUDED
