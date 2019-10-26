#ifndef SBR_H
#define SBR_H

#include <vector>
#include <iostream>

class SBR{
	
	public:

		//Construtor.
		SBR(int n){
			//Alocando a matriz  de adjacência.
			V = n;
			int** ma = new int*[V];
			for(auto i(0); i < V; i++){
				ma[i] = new int[V];
				for(auto j(0); j < V; j++){
					ma[i][j] = 0;
				}
			}

			m = ma;			

			//Alocando vetor de cargas.
			int *Ca = new int[V];
			for(auto i(0); i < V; i++){
				Ca[i] = 0;
			}

			C = Ca; 
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
	//Realiza a leitura pelo da carga de alunos por parada.
	void loadStudentsPerStop(std::string filename);

	/***************************************************** FUNÇÕES DE AUXÍLIO ****************************************************/
	//Mostra o estado do grafo.
	void showGraph(void);
	void showStudentsPerStop(void);

	private:
		//Matriz de adjacência contendo as distâncias entre os vértices (não adjcência representada pelo valor 0).
		int** m;
		//Número de vértices.
		int V;
		//Carga a ser coletada (Número de alunos nas paradas).
		int* C;
};

#endif