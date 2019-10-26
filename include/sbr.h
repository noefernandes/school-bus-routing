#ifndef SBR_H
#define SBR_H

#include <vector>
#include <iostream>

class SBR{
	
	public:

		//Construtor.
		SBR(int n){

			V = n;
			int** ma = new int*[V];

			for(auto i(0); i < V; i++){
				ma[i] = new int[V];
				for(auto j(0); j < V; j++){
					ma[i][j] = 0;
				}
			}

			m = ma;			
		}

		//Destrutor.
		~SBR(){
			for(auto i(0); i < V; i++){
				delete[] m[i];
			}

			delete m;			
		}

	/*********************************************** FUNÇÕES DE MANIPULAÇÃO DO GRAFO *********************************************/
	//Retorna a matriz de adjacência.
	int** getAdjacencyMatrix(void);
	//Insere uma aresta no grafo.
	void insertEdge(int a, int b, int cost);
	//Remove uma aresta do grafo.
	void removeEdge(int a, int b);
	//Retorna o vértice adjacente de menor custo.
	int smallestAdjacentVertex(int a);
	//Retorna o custo do aresta.
	int getEdgeCost(int a, int b);

	/***************************************************** FUNÇÕES DE AUXÍLIO ****************************************************/
	//Mostra o estado do grafo.
	void showGraph(void);

	private:
		//Matriz de adjacência.
		int** m;
		int V;
};

#endif