#include "Grafo.hpp"
#include <iostream>
#include <limits>
using namespace std;

Grafo_LA::Grafo_LA(int numVertices){
    n = 0;
    inicializar(numVertices);
    status = new Status[numVertices+1];
    for(int i = 1; i <= numVertices; i++)
        status[i] = Amigo;
}

Grafo_LA::~Grafo_LA(){
    destruir();
}

void Grafo_LA::inicializar(int numVertices){
    n = numVertices;
    m = 0;
    adj = new ListaLigada<Vertice>[n+1];
    status = new Status[n+1];
    pesos = new int*[n+1];
    for(Vertice u = 1; u <= numVertices; u++)
        status[u] = Amigo;
    for(int i = 1; i <= n; i++){
        pesos[i] = new int[n+1];
        for(int j = 1; j <= n; j++)
            pesos[i][j] = -1;
    }
}

void Grafo_LA::destruir(){
    for(int i = 0; i <= n; i++)
        adj[i].esvaziar();
    delete [] adj;
    for(int i = 1; i <= n; i++)
        delete [] pesos[i];
    delete [] pesos;
    n = m = 0;
}

void Grafo_LA::reinicializar(int numVertices){
    destruir();
    inicializar(numVertices);
}

void Grafo_LA::marcarInimigo(Vertice u){
    status[u] = Inimigo;
}

void Grafo_LA::inserirAresta(Vertice u, Vertice v, Peso p){
    adj[u].inserir(v);
    adj[v].inserir(u);
    if(pesos[u][v] != -1 || pesos[v][u] != -1){ //o peso já existir é um erro, estamos trabalhando com grafos simples
        cout << "ERRO";
        exit(123);
    }
    pesos[u][v] = p;
    pesos[v][u] = p;
    m++;
}

void Grafo_LA::inserirArestaDirecionada(Vertice u, Vertice v, Peso p){
    adj[u].inserir(v);
    if(pesos[u][v] != -1){ //o peso já existir é um erro, estamos trabalhando com grafos simples
        cout << "ERRO";
        exit(123);
    }
    pesos[u][v] = p;
    m++;
}

void Grafo_LA::removerAresta(Vertice u, Vertice v){

}

void Grafo_LA::mostrar(){
    for(int i = 1; i <= n; i++){
        cout << "Vertice " << i << ": " << endl;
        adj[i].mostrarLista();
    }
}

int Grafo_LA::getTamanho() const{
    return n;
}

int Grafo_LA::getNumArestas() const{
    return m;
}

int** Grafo_LA::getPesos() const{
    return pesos;
}

Status* Grafo_LA::getStatus() const{
    return status;
}

ListaLigada<Vertice>* Grafo_LA::getAdj(){
    return adj;
}




/*
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
*******************************************************************************************************************
*******************************************************************************************************************
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                                                                                                 */




BuscaEmProfundidade::BuscaEmProfundidade(){
    cor = nullptr;
    predecessorVertice = tempoEntrada = tempoSaida = nullptr;
    somatorio = 0;
}

BuscaEmProfundidade::~BuscaEmProfundidade(){
    if(cor != nullptr)
        delete [] cor;
    if(predecessorVertice != nullptr)
        delete [] predecessorVertice;
    if(tempoEntrada != nullptr)
        delete [] tempoEntrada;
    if(tempoSaida != nullptr)
        delete [] tempoSaida;
}


void BuscaEmProfundidade::DFS(Grafo_LA& G){
    tempo = 0;
    cor = new Cor [G.getTamanho()+1];
    predecessorVertice = new int [G.getTamanho()+1];
    tempoEntrada = new int [G.getTamanho()+1];
    tempoSaida = new int [G.getTamanho()+1];

    for(Vertice u = 1; u <= G.getTamanho(); u++){
        cor[u] = Branco;
        predecessorVertice[u] = -1;
    }
    for(Vertice u = 1; u <= G.getTamanho(); u++)
        if(cor[u] == Branco)
            DFS_VISITA(G, u);
}

void BuscaEmProfundidade::DFS_VISITA(Grafo_LA& G, int u){
    tempo++;
    tempoEntrada[u] = tempo;
    cor[u] = Cinza;
    int* adjacenciaVertice = G.getAdj()[u].retornaInteiros(); //retorna inteiros nos dá uma vetor com os inteiros referentes aos vertices adjacentes a u
    int tam = adjacenciaVertice[0];
    adjacenciaVertice[0] = -1;

    //cout << "Vertice: " << u << '\n';
    /*for(int i = 1; i < tam; i++)
        cout << adjacenciaVertice[i] << '\n';
    cout << '\n';
    printa as adjacencias*/



    for(Vertice v = 1; v < tam; v++){
        if(cor[adjacenciaVertice[v]] == Branco){
            somatorio += G.getPesos()[u][adjacenciaVertice[v]];
            predecessorVertice[adjacenciaVertice[v]] = u;
            DFS_VISITA(G, adjacenciaVertice[v]);
        }
    }

    cor[u] = Preto;
    tempo++;
    tempoSaida[u] = tempo;
    ordemTopologica.inserirInicio(u);
}


float BuscaEmProfundidade::getSomatorio() const{
    return somatorio;
}





BuscaEmLargura::BuscaEmLargura(){
    cor = nullptr;
    predecessorVertice = nullptr;
    distancia = nullptr;
    distAtual = 0;
}

BuscaEmLargura::~BuscaEmLargura(){
    if(cor != nullptr)
        delete [] cor;
    if(predecessorVertice != nullptr)
        delete [] predecessorVertice;
    if(distancia != nullptr)
        delete [] distancia;
}

void BuscaEmLargura::BFS(Grafo_LA& G, Vertice u){
    cor = new Cor [G.getTamanho()+1];
    predecessorVertice = new int [G.getTamanho()+1];
    distancia = new int[G.getTamanho()+1];
    for(Vertice t = 1; t <= G.getTamanho(); t++){
        cor[t] = Branco;
        predecessorVertice[t] = -1;
        distancia[t] = -1;
    }
    cor[u] = Cinza;
    distancia[u] = 0;
    fila.adicionar(u);
    while(!fila.estaVazia()){
        u = fila.pop();
        int* adjacenciaVertice = G.getAdj()[u].retornaInteiros();
        for(Vertice v = 1; v < adjacenciaVertice[0]; v++)
            if(cor[adjacenciaVertice[v]] == Branco && G.getStatus()[adjacenciaVertice[v]] != Inimigo){
                cor[adjacenciaVertice[v]] = Cinza;
                distancia[adjacenciaVertice[v]] = distancia[u] + 1;
                predecessorVertice[adjacenciaVertice[v]] = u;
                fila.adicionar(adjacenciaVertice[v]);
            }
        cor[u] = Preto;
    }
}

int* BuscaEmLargura::getDistancia() const{
    return distancia;
}

int* BuscaEmLargura::getPredecessores() const{
    return predecessorVertice;
}
