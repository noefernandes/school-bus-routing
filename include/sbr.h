#ifndef SBR_H
#define SBR_H

#include <vector>
#include <iostream>

struct Pair{
	int leftVertex;
	int rightVertex;
	int saved;

	Pair(){
		leftVertex = -1;
		rightVertex = -1;
		saved = 0;
	}
};

class SBR{
	
	public:

		//Construtor.
		SBR(int n, int capacity, int bus){
			BusCapacity = capacity;
			numberOfBus = bus;
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

			//Colocando numero de rotas.
			//routes.resize(3);
			routes.resize(numberOfBus);
		}

		//Destrutor.
		~SBR(){
			for(auto i(0); i < V; i++){
				delete[] m[i];
			}
			delete m;	
			delete C;		
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
	//Carrega o peso dos vértices (quantidade de alunos por parada)
	void loadVertexWeight(std::fstream & File);
	//Eurística de Clark & Wright na versão sequencial: encontra as rotas que cada ônibus percorrerá.
	void clarkeAndWright(std::ofstream & OutputFile);

	/***************************************************** FUNÇÕES DE AUXÍLIO ****************************************************/
	//Mostra o estado do grafo.
	void showGraph(void);
	//Mostra o número de estudantes por parada.
	void showStudentsPerStop(void);
	//Retorna distância da rota.
	int getRouteDistance(int i);
	//Retorna o número de paradas na rota.
	int getNumberOfStops(int i);
	//Calcula a quantidade total de alunos pegos em determinada rota.
	int getWeight(int i);
	//Testa se a quantidade total de alunos seria válida para a inserção de um vértice na rota. 
	bool weightIsCorrect(int vertex, int i);


	private:
		//Matriz de adjacência contendo as distâncias entre os vértices (não adjcência representada pelo valor 0).
		int** m;
		//Número de vértices.
		int V;
		//Número de ônibus. 
		int numberOfBus;
		// Capacidade do ônibus
		int BusCapacity; 
		//Carga a ser coletada (Número de alunos nas paradas).
		int* C;
		//Vector com todas as rotas formadas.
		std::vector<std::vector<int>> routes;
};

#endif
