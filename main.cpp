#include <iostream>
#include <limits>
using namespace std;

#include "Grafo.hpp"
#include "Pilha.hpp"
#include "ListaLigada.hpp"
#include "Fila.hpp"


int main(){
    //leitura de dados inicial/leitura do grafo galáxia

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
    // acaba o preenchimento do grafo galáxia
    int qtdInimigos;
    cin >> qtdInimigos;
    for(int i = 0; i < qtdInimigos; i++){
        int sistemaInimigo;
        cin >> sistemaInimigo;
        galaxia.marcarInimigo(sistemaInimigo);
    }//vertices são marcados como inimigos

    int sistemaInicial, sistemaDestino;
    cin >> sistemaInicial;
    cin >> sistemaDestino;



    Grafo_LA** sistPlanetarios = new Grafo_LA*[ordemGrafo+1]; //cada posicao [i] vai se referir a um vertice do grafo galaxia

    //leitura de dados dos sistemas planetários
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
    menorCaminho.BFS(galaxia, sistemaInicial); //monta a arvore de distancias minimas

    Pilha<int> sistemasVisitados;
    cout << '\n';
    int sistemaAtual = sistemaDestino;
    sistemasVisitados.adicionar(sistemaDestino);
    while(sistemaAtual != sistemaInicial){ //colocamos na fila cada sistema que foi visitado durando a BFS
        cout << "predecessor do sistema " << sistemaAtual << ": " << menorCaminho.getPredecessores()[sistemaAtual] << '\n';
        sistemaAtual = menorCaminho.getPredecessores()[sistemaAtual];
        sistemasVisitados.adicionar(sistemaAtual);
    }
    sistemasVisitados.mostrarPilha();
    cout << "\n\n\n\n";
    float somatorio = 0;
    while(!sistemasVisitados.estaVazia()){ //para cada sistema que está na pilha vamos pegar o somatório
        BuscaEmProfundidade busca = BuscaEmProfundidade();
        Vertice u = sistemasVisitados.pop();
        busca.DFS(*sistPlanetarios[u]);
        somatorio += busca.getSomatorio();
    }
    cout << float(somatorio) << ".0";





}
