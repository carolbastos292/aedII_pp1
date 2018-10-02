#include "Grafo.hpp"
//#include "UnionFind.hpp"
//#include "heapsort.hpp"
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
    pesos = new int*[n+1];
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


Grafo_MA::Grafo_MA(int numVertices){
    inicializar(numVertices);
}

Grafo_MA::~Grafo_MA(){
    destruir();
}

void Grafo_MA::inicializar(int numVertices){
    n = numVertices;
    mat = new int*[n+1];
    mat[0] = nullptr;
    for(int i = 1; i <= n; i++){
        mat[i] = new int[n+1];
        for(int j = 1; j <= n; j++)
            mat[i][j] = 0;
    }
    pesos = new int*[n+1];
    for(int i = 1; i <= n; i++){
        pesos[i] = new int[n+1];
        for(int j = 1; j <= n; j++)
            pesos[i][j] = -1;
    }
}

void Grafo_MA::destruir(){
    for(int i = 1; i <= n; i++)
        delete [] mat[i];
    delete [] mat;
}

void Grafo_MA::reinicializar(int numVertices){
    destruir();
    inicializar(numVertices);
}

void Grafo_MA::inserirAresta(Vertice u, Vertice v, Peso p){
    mat[u][v]++;
    mat[v][u]++;
    if(pesos[u][v] != -1 || pesos[v][u] != -1){ //o peso já existir é um erro, estamos trabalhando com grafos simples
        cout << "ERRO";
        exit(123);
    }
    pesos[u][v] = p;
    pesos[v][u] = p;
    m++;
}

void Grafo_MA::removerAresta(Vertice u, Vertice v){
    mat[u][v]--;
    mat[v][u]--;
    m--;
}

void Grafo_MA::mostrar(){
//    for(int i = 0; i <= n; i++)
    cout << '\t';
    for(int i = 1; i<= n; i++)
        cout << '[' << i << ']' << '\t';
    cout << '\n';

    for(int i = 1; i <= n; i++){
        cout << '[' << i << ']' << '\t';
        for(int j = 1; j <= n; j++)
            cout << mat[i][j] << '\t';
        cout << '\n';
    }
}

int Grafo_MA::getTamanho(){
    return n;
}

int** Grafo_MA::getMatriz() const{
    return mat;
}

int** Grafo_MA::getPesos() const{
    return pesos;
}







BuscaEmProfundidade::BuscaEmProfundidade(){
    cor = nullptr;
    predecessorVertice = tempoEntrada = tempoSaida = nullptr;
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
    cout << "Vertice: " << u << '\n';
    tempo++;
    tempoEntrada[u] = tempo;
    cor[u] = Cinza;
    int* adjacenciaVertice = G.getAdj()[u].retornaInteiros(); //retorna inteiros nos dá uma vetor com os inteiros referentes aos vertices adjacentes a u

    /*for(int i = 1; i < adjacenciaVertice[0]; i++)
        cout << adjacenciaVertice[i] << '\n';
    cout << '\n';
    printa as adjacencias */

    for(Vertice v = 1; v < adjacenciaVertice[0]; v++){ //a posicao 0 apenas indica quantos elementos existem no vetor. Que engenhoso
        if(cor[adjacenciaVertice[v]] == Branco){
            predecessorVertice[adjacenciaVertice[v]] = u;
            DFS_VISITA(G, adjacenciaVertice[v]);
        }
    }

    cor[u] = Preto;
    tempo++;
    tempoSaida[u] = tempo;
    ordemTopologica.inserirInicio(u);
}



BuscaEmProfundidade_MA::BuscaEmProfundidade_MA(){
    cor = nullptr;
    predecessorVertice = tempoEntrada = tempoSaida = nullptr;
}

BuscaEmProfundidade_MA::~BuscaEmProfundidade_MA(){
    if(cor != nullptr)
        delete [] cor;
    if(predecessorVertice != nullptr)
        delete [] predecessorVertice;
    if(tempoEntrada != nullptr)
        delete [] tempoEntrada;
    if(tempoSaida != nullptr)
        delete [] tempoSaida;
}

void BuscaEmProfundidade_MA::DFS(Grafo_MA& G){
    tempo = 0;
    cor = new Cor[G.getTamanho()+1];
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

void BuscaEmProfundidade_MA::DFS_VISITA(Grafo_MA& G, int u){
    cout << "Vertice: " << u << '\n';
    tempo++;
    tempoEntrada[u] = tempo;
    cor[u] = Cinza;


    for(int v = 1; v <= G.getTamanho(); v++){
        int a = G.getMatriz()[u][v];
        if(a != 0) //!= 0 pois a quando uma posicao é 0 é porque não existem arestas
            if(cor[v] == Branco){
            predecessorVertice[v] = u;
            DFS_VISITA(G, v);
        }
    }

    cor[u] = Preto;
    tempo++;
    tempoSaida[u] = tempo;
    ordemTopologica.inserirInicio(u);
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

void BuscaEmLargura::BFS(Grafo_LA& G, Vertice u, Vertice v){
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
            if(cor[adjacenciaVertice[v]] == Branco){
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



BuscaEmLargura_MA::BuscaEmLargura_MA(){
    cor = nullptr;
    predecessorVertice = nullptr;
    distancia = nullptr;
    distAtual = 0;
}

BuscaEmLargura_MA::~BuscaEmLargura_MA(){
    if(cor != nullptr)
        delete [] cor;
    if(predecessorVertice != nullptr)
        delete [] predecessorVertice;
    if(distancia != nullptr)
        delete [] distancia;
}

void BuscaEmLargura_MA::BFS(Grafo_MA& G, Vertice u){
    cor = new Cor [G.getTamanho()+1];
    predecessorVertice = new int [G.getTamanho()+1];
    distancia = new int [G.getTamanho()+1];

    for(Vertice v = 1; v <= G.getTamanho(); v++){
        cor[v] = Branco;
        predecessorVertice[v] = -1;
        distancia[v] = -1;
    }
    cor[u] = Cinza;
    distancia[u] = 0;
    predecessorVertice[u] = -1;
    fila.adicionar(u);
    while(!fila.estaVazia()){
        u = fila.pop();
        for(Vertice v = 1; v <= G.getTamanho(); v++){
            int a = G.getMatriz()[u][v];
            if(a != 0)
                if(cor[v] == Branco){
                    cor[v] = Cinza;
                    distancia[v] = distancia[u] + 1;
                    predecessorVertice[v] = u;
                    fila.adicionar(v);
                }
        }
        cor[u] = Preto;
    }
}

int* BuscaEmLargura_MA::getDistancia() const{
    return distancia;
}






MST::MST(){
    chave = pai = nullptr;
    fila = nullptr;
}

MST::~MST(){
    destruir();
}

void MST::reinicializar(){
    destruir();
    chave = pai = nullptr;
    fila = nullptr;
}

void MST::destruir(){
    if(chave != nullptr)
        delete [] chave;
    if(pai != nullptr)
        delete [] pai;
    if(fila != nullptr)
        delete fila;
}

void MST::MST_Prim(Grafo_LA& G, Vertice r){
    n = G.getTamanho();
    fila = new FilaPrioridades(n);
    chave = new int[n+1];
    pai = new int[n+1];

    for(int i = 1; i <= n; i++){
        chave[i] = INT_MAX;
        pai[i] = -1;
    }
    chave[r] = 0;
    for(int i = 1; i <= n; i++)
        fila->inserir(i, chave[i]);
    while(!fila->estaVazia()){
        Vertice u = fila->extrairMinimo().vertice;
        int* a = G.getAdj()[u].retornaInteiros();
        for(int i = 1; i < a[0]; i++){
            Vertice v = a[i];
            if(fila->estaNaFila(v) && G.getPesos()[u][v] < chave[v]){
                pai[v] = u;
                chave[v] = G.getPesos()[u][v];
                fila->atualizarPrioridade(v, chave[v]);
            }
        }
    }
}

void MST::MST_Kruskal(Grafo_LA& G){

}

void MST::mostrar(Grafo_LA& G){
    for(int i = 1; i <= n; i++){
        cout << "Vertice: " << i << '\n';
        if(pai[i] == -1){
            cout << "Este vertice eh a raiz" << "\n\n";
            continue;
        }
        cout << "Pai: " << pai[i] << '\n';
        cout << "Peso: " << G.getPesos()[i][pai[i]] << '\n';
        cout << '\n';
    }
    mostrarSomatorio(G);
}

void MST::mostrarSomatorio(Grafo_LA& G){
    int n = G.getTamanho();
    int soma = 0;
    for(int i = 1; i <= n; i++)
        soma += chave[i];
    cout << "O somatorio das chaves eh: " << soma << '\n';
}







MST_MA::MST_MA(){
    chave = pai = nullptr;
    fila = nullptr;
}

MST_MA::~MST_MA(){
    destruir();
}

void MST_MA::destruir(){
    if(chave != nullptr)
        delete [] chave;
    if(pai != nullptr)
        delete [] pai;
    if(fila != nullptr)
        delete fila;
}

void MST_MA::reinicializar(){
    destruir();
    pai = chave = nullptr;
    fila = nullptr;
}

void MST_MA::MST_Prim(Grafo_MA& G, Vertice r){
    int n = G.getTamanho();
    chave = new int[n+1];
    pai = new int[n+1];
    fila = new FilaPrioridades(n);
    for(int i = 1; i <= n; i++){
        chave[i] = INT_MAX;
        pai[i] = -1;
    }
    chave[r] = 0;
    for(int i = 1; i <= n; i++)
        fila->inserir(i, chave[i]);
    int** a = G.getMatriz();
    while(!fila->estaVazia()){
        Vertice u = fila->extrairMinimo().vertice;
        for(Vertice v = 1; v <= n; v++)
            if(a[u][v] != 0)
                if(fila->estaNaFila(v) && G.getPesos()[u][v] < chave[v]){
                    pai[v] = u;
                    chave[v] = G.getPesos()[u][v];
                    fila->atualizarPrioridade(v, chave[v]);
                }
    }
}

void MST_MA::MST_Kruskal(Grafo_MA& G){

}

void MST_MA::mostrar(Grafo_MA& G){
    int n = G.getTamanho();
    for(int i = 1; i <= n; i++){
        cout << "Vertice: " << i << '\n';
        if(pai[i] == -1){
            cout << "Este vertice eh a raiz" << "\n\n";
            continue;
        }
        cout << "Pai: " << pai[i] << '\n';
        cout << "Peso: " << G.getPesos()[i][pai[i]] << '\n';
        cout << '\n';
    }
    mostrarSomatorio(G);
}

void MST_MA::mostrarSomatorio(Grafo_MA& G){
    int n = G.getTamanho();
    int soma = 0;
    for(int i = 1; i <= n; i++)
        soma += chave[i];
    cout << "O somatorio das chaves eh: " << soma << '\n';
}






Dijkstra::Dijkstra(){
    pai = distancia = nullptr;
    peso = nullptr;;
    fila = nullptr;
}

Dijkstra::~Dijkstra(){
    if(pai != nullptr)
        delete [] pai;
    if(distancia != nullptr)
        delete [] distancia;
    if(fila != nullptr)
        delete fila;
}

void Dijkstra::menorCaminho(Grafo_LA& G, Vertice r){
    raiz = r;
    n = G.getTamanho();
    peso = G.getPesos();
    pai = new int[n+1];
    distancia = new int[n+1];
    fila = new FilaPrioridades(n);
    for(Vertice u = 1; u <= n; u++){
        pai[u] = -1;
        distancia[u] = INT_MAX;
    }
    distancia[r] = 0;
    for(Vertice u = 1; u <= n; u++)
        fila->inserir(u, distancia[u]);

    while(!fila->estaVazia()){
        Vertice u = fila->extrairMinimo().vertice;
        int* a = G.getAdj()[u].retornaInteiros();
        for(Vertice v = 1; v < a[0]; v++){
            relaxa(u, a[v]);
        }
    }
}

void Dijkstra::relaxa(Vertice u, Vertice v){
    if(distancia[v] > distancia[u] + peso[u][v]){
        distancia[v] = distancia[u] + peso[u][v];
        fila->atualizarPrioridade(v, distancia[v]);
        pai[v] = u;
    }
}

void Dijkstra::mostrarDistancia(){
    cout << "Raiz: " << raiz << '\n';
    for(int i = 1; i <= n; i++){
        cout << "Distancia ate o vertice " << i << ": " << distancia[i] << '\n';
    }
    cout << '\n';
}
