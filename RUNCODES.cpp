#include <iostream>
#include <cstdio>
#include <limits>
using namespace std;


typedef int Vertice;
typedef float Peso;
enum Cor {Branco, Cinza, Preto};
enum Status {Amigo, Inimigo};


template<typename T>
class ELEMENTO{
public:
    T getDados();
    ELEMENTO* prox,* antc;
    T dados;
};

template<typename T>
T ELEMENTO<T>::getDados(){
    return dados;
}


template<typename T>
class ListaLigada{
public:
    ListaLigada();
    ~ListaLigada();
    void inserir(T);
    void inserirInicio(T);
    void esvaziar();
    bool estaVazia() const;
    int getTamanho() const;
    int* retornaInteiros();
private:
    ELEMENTO<T>* inicio;
    int tamanho;
};

template<typename T>
class Pilha{
public:
    Pilha();
    ~Pilha();
    void adicionar(T);
    T pop();
    void esvaziar();
    bool estaVazia() const;
private:
    ELEMENTO<T>* topo;
};


struct PRIORIDADE{
    int vertice;
    int prioridade;
};

class FilaPrioridades{
private:
public:
    FilaPrioridades(int tam){
        elemento = new PRIORIDADE[tam];
        qtd = 0;
    }

    ~FilaPrioridades(){
        delete [] elemento;
    }

    PRIORIDADE* elemento;
    int qtd;

    void inserir(int vertice, int prioridade){
        elemento[qtd].vertice = vertice;
        elemento[qtd].prioridade = prioridade;
        qtd++;
    }
    bool estaVazia(){
        return qtd == 0 ? true : false;
    }

    bool estaNaFila(int n){
        for(int i = 0; i < qtd; i++)
            if(elemento[i].vertice == n)
                return true;
        return false;
    }

    PRIORIDADE extrairMinimo(){
        if(qtd == 0)
            exit(123);
        int min = 0;
        for(int i = 0; i < qtd; i++)
            if(elemento[i].prioridade < elemento[min].prioridade)
                min = i;

        PRIORIDADE a;
        a.prioridade = elemento[min].prioridade;
        a.vertice = elemento[min].vertice;

        for(int i = min; i < qtd-1; i++){
            elemento[i] = elemento[i+1];
        }
        qtd--;
        return a;
    }
    void atualizarPrioridade(int v, int novaPrio){
        for(int i = 0; i < qtd; i++)
            if(elemento[i].vertice == v){
                elemento[i].prioridade = novaPrio;
                return;
            }
    }
};


template<typename T>
class Fila{
    public:
        Fila();
        ~Fila();
        void adicionar(T);
        void remover();
        T extrairMinimo();
        T pop();
        bool estaVazia() const;
        void esvaziar();
    private:
        ELEMENTO<T>* primeiro,* ultimo;
};





class Grafo_LA{
public:
    Grafo_LA(int);
    ~Grafo_LA();
    void inserirAresta(Vertice, Vertice, Peso = 0);
    ListaLigada<Vertice>* getAdj();
    int** getPesos() const;
    int getTamanho() const;
    int getNumArestas() const;
    Status* getStatus() const;
    void marcarInimigo(Vertice);
private:
    Status* status;
    int** pesos;
    void inicializar(int);
    void destruir();
    ListaLigada<Vertice>* adj;
    int n, m;
};



class BuscaEmProfundidade{
public:
    BuscaEmProfundidade();
    ~BuscaEmProfundidade();
    void DFS(Grafo_LA&);
    void DFS_VISITA(Grafo_LA&, int);
    float getSomatorio() const;
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








int main(){

    int ordemGrafo, numArestas;
    cin >> ordemGrafo;
    cin >> numArestas;

    Grafo_LA galaxia(ordemGrafo);
    for(int i = 0; i < numArestas; i++){
        int aresta1, aresta2;
        cin >> aresta1;
        cin >> aresta2;
        galaxia.inserirAresta(aresta1, aresta2);
    }

    int qtdInimigos;
    cin >> qtdInimigos;
    for(int i = 0; i < qtdInimigos; i++){
        int sistemaInimigo;
        cin >> sistemaInimigo;
        galaxia.marcarInimigo(sistemaInimigo);
    }

    int sistemaInicial, sistemaDestino;
    cin >> sistemaInicial;
    cin >> sistemaDestino;



    Grafo_LA** sistPlanetarios = new Grafo_LA*[ordemGrafo+1];

    for(int i = 1; i <= ordemGrafo; i++){
        int ordemSistPlanetario, arestasSistPlanetario;
        cin >> ordemSistPlanetario;
        cin >> arestasSistPlanetario;

        sistPlanetarios[i] = new Grafo_LA(ordemSistPlanetario);
        for(int j = 0; j < arestasSistPlanetario; j++){
            int aresta1, aresta2;
            float distanciaEntrePlanetas;
            cin >> aresta1;
            cin >> aresta2;
            cin >> distanciaEntrePlanetas;
            sistPlanetarios[i]->inserirAresta(aresta1, aresta2, distanciaEntrePlanetas);
        }
    }

    BuscaEmLargura menorCaminho;
    menorCaminho.BFS(galaxia, sistemaInicial);
    Pilha<int> sistemasVisitados;
    int sistemaAtual = sistemaDestino;
    sistemasVisitados.adicionar(sistemaDestino);

    while(sistemaAtual != sistemaInicial){
        sistemaAtual = menorCaminho.getPredecessores()[sistemaAtual];
        sistemasVisitados.adicionar(sistemaAtual);
    }

    float somatorio = 0;
    while(!sistemasVisitados.estaVazia()){
        BuscaEmProfundidade busca = BuscaEmProfundidade();
        Vertice u = sistemasVisitados.pop();
        busca.DFS(*sistPlanetarios[u]);
        somatorio += busca.getSomatorio();
    }

    cout << float(somatorio) << ".0";
}






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

void Grafo_LA::marcarInimigo(Vertice u){
    status[u] = Inimigo;
}

void Grafo_LA::inserirAresta(Vertice u, Vertice v, Peso p){
    adj[u].inserir(v);
    adj[v].inserir(u);
    if(pesos[u][v] != -1 || pesos[v][u] != -1){
        cout << "ERRO";
        exit(123);
    }
    pesos[u][v] = p;
    pesos[v][u] = p;
    m++;
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
    int* adjacenciaVertice = G.getAdj()[u].retornaInteiros();
    int tam = adjacenciaVertice[0];
    adjacenciaVertice[0] = -1;

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






template<typename T>
ListaLigada<T>::ListaLigada(){
    inicio = nullptr;
    tamanho = -1;
}

template<typename T>
ListaLigada<T>::~ListaLigada(){
    esvaziar();
}

template<typename T>
void ListaLigada<T>::inserir(T dado){
    if(inicio == nullptr){
        inicio = new ELEMENTO<T>;
        inicio->dados = dado;
        inicio->prox = nullptr;
        tamanho++;
        return;
    }
    ELEMENTO<T>* e = inicio;
    while(e->prox != nullptr)
        e = e->prox;
    e->prox = new ELEMENTO<T>;
    e = e->prox;
    e->dados = dado;
    e->prox = nullptr;
    tamanho++;
}

template<typename T>
void ListaLigada<T>::inserirInicio(T dado){
    if(inicio == nullptr){
        inicio = new ELEMENTO<T>;
        inicio->dados = dado;
        inicio->prox = nullptr;
        tamanho++;
        return;
    }
    ELEMENTO<T>* e = new ELEMENTO<T>;
    e->dados = dado;
    e->prox = inicio;
    inicio = e;
    tamanho++;
}

template<typename T>
void ListaLigada<T>::esvaziar(){
    ELEMENTO<T>* e = inicio, * excluir;
    while(e != nullptr){
        excluir = e;
        e = e->prox;
        delete excluir;
        excluir = nullptr;
    }
    inicio = nullptr;
    tamanho = -1;
}

template<typename T>
bool ListaLigada<T>::estaVazia() const{
    return inicio == nullptr ? true : false;
}

template<typename T>
int ListaLigada<T>::getTamanho() const{
    return tamanho;
}


template<typename T>
int* ListaLigada<T>::retornaInteiros(){
    int* retorno = new int[tamanho+2];
    retorno[0] = tamanho+2;
    ELEMENTO<T>* e = inicio;
    int i = 1;
    while(e != nullptr){
        retorno[i] = e->dados;
        i++;
        e = e->prox;
    }
    return retorno;
}







template<typename T>
Pilha<T>::Pilha(){
    topo = nullptr;
}

template<typename T>
Pilha<T>::~Pilha(){
    esvaziar();
}

template<typename T>
void Pilha<T>::adicionar(T dado){
    if(topo == nullptr){
        topo = new ELEMENTO<T>;
        topo->dados = dado;
        topo->prox = nullptr;
        return;
    }
    ELEMENTO<T>* e = topo;
    topo = new ELEMENTO<T>;
    topo->dados = dado;
    topo->prox = e;
}


template<typename T>
T Pilha<T>::pop(){
    T retorno = topo->dados;
    ELEMENTO<T>* e = topo->prox;
    delete topo;
    topo = e;
    return retorno;
}

template<typename T>
void Pilha<T>::esvaziar(){
    ELEMENTO<T>* e = topo,* excluir;
    while(e != nullptr){
        excluir = e;
        e = e->prox;
        delete excluir;
    }
}

template<typename T>
bool Pilha<T>::estaVazia() const{
    return topo == nullptr ? true : false;
}





template<typename T>
Fila<T>::Fila(){
    primeiro = nullptr;
    ultimo = nullptr;
}

template<typename T>
Fila<T>::~Fila(){
    esvaziar();
}

template<typename T>
void Fila<T>::adicionar(T dado){
    if(primeiro == nullptr){
        primeiro = new ELEMENTO<T>;
        primeiro->dados = dado;
        primeiro->prox = nullptr;
        ultimo = primeiro;
        return;
    }
    ELEMENTO<T>* e = ultimo;
    e->prox = new ELEMENTO<T>;
    e->prox->dados = dado;
    e->prox->prox = nullptr;
    ultimo = e->prox;
}

template<typename T>
void Fila<T>::remover(){
    if(primeiro == nullptr){
        return;
    }
    if(primeiro == ultimo){
        delete primeiro;
        primeiro = ultimo = nullptr;
        return;
    }
    ELEMENTO<T>* e = primeiro->prox;
    delete primeiro;
    primeiro = e;
}

template<typename T>
T Fila<T>::extrairMinimo(){

}


template<typename T>
T Fila<T>::pop(){
    if(primeiro == nullptr){
        throw bad_alloc();
    }
    if(primeiro == ultimo){
        T dado = primeiro->dados;
        delete primeiro;
        primeiro = ultimo = nullptr;
        return dado;
    }
    T dado = primeiro->dados;
    ELEMENTO<T>* e = primeiro->prox;
    delete primeiro;
    primeiro = e;
    return dado;
}

template<typename T>
bool Fila<T>::estaVazia() const{
    return primeiro == nullptr ? true : false;
}


template<typename T>
void Fila<T>::esvaziar(){
    ELEMENTO<T>* e = primeiro,* excluir;
    while(e != nullptr){
       excluir = e;
       e = e->prox;
       delete excluir;
    }
}
