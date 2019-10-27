#include "sbr.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 
#include <vector>

double** SBR::getAdjacencyMatrix(void){
	return m;
}

void SBR::insertEdge(int a, int b, double cost = 0){
	m[a][b] = cost;
	m[b][a] = cost;
}

void SBR::removeEdge(int a, int b){
	m[a][b] = 0;
	m[b][a] = 0;
}

double SBR::getEdgeCost(int a, int b){
	return m[a][b];
}

void SBR::showGraph(void){
	for(auto i(0); i < V; i++){
		for(auto j(0); j < V; j++){
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int SBR::smallestAdjacentVertex(int a){
	int smallestEdge = std::numeric_limits<int>::max();
	int smallestVertex = 0;
	for(auto i(0); i < V; i++){
		if(m[a][i] < smallestEdge and m[a][i] != 0){
			smallestEdge = m[a][i];
			smallestVertex = i;
		}
	}
	return smallestVertex;
}

void SBR::loadStudentsPerStop(std::string filename){
	std::ifstream ifs("files/" + filename);
	std::string line;
	int i(0);
  	if (ifs.is_open()){
    	while(getline(ifs,line)){
      		C[i] = stoi(line);
      		i++;
    	}
    	ifs.close();
  	}
}

bool comparePair(Pair p1, Pair p2) { 
    return p1.saved > p2.saved; 
} 


void SBR::showStudentsPerStop(void){
	for(auto i(0); i < V; i++){
		std::cout << C[i] << " ";
	}
	std::cout << std::endl;
}

double SBR::getRouteDistance(int i){
	double sumRoute = 0;
	for(unsigned int j(0); j < routes[i].size() - 1; j++){
		sumRoute += m[routes[0][j]][routes[0][j+1]];
	}
	return sumRoute;
}

int SBR::getNumberOfStops(int i){
	int stops = -1;
	for(unsigned int j(0); j < routes[i].size() - 1; j++){
		stops++;
	}
	return stops;
}

double SBR::getWeight(int i){
	double pesoTotal = 0;

	for(unsigned int j(0); j < routes[0].size() - 2; j++){
		pesoTotal += C[routes[0][j+1] - 1];
	}

	return pesoTotal;
}

/*std::vector<std::string>*/void SBR::clarkeAndWright(void){
	//Vetor de economias.
	double** E = new double*[V];

	for(auto i(0); i < V; i++){
		E[i] = new double[V];
		for(auto j(0); j < V; j++){
			E[i][j] = 0;
		}
	}

	//Encontrando os valores de economia para cada pares de nós.
	for(auto i(0); i < V; i++){
		for(auto j(0); j < V; j++){
			if(i != 0 and j != 0 and i != j){
				E[i][j] = m[0][i] + m[0][j] - m[i][j];
			}
		}
	}






	/****************************Ordenando cada par de vértices por sua economia de forma decrescente****************************/

	



	//Criando matriz com valor de economia por par, vertice extremo esquerdo e vertice extremo direito.
	std::vector<Pair> pairsList;

	for(auto i(1); i < V; i++){
		for(auto j(i + 1); j < V; j++){
			Pair pair;
			pair.saved = E[i][j];
			pair.leftVertex = i;
			pair.rightVertex = j;
			pairsList.push_back(pair);
		}
	}

	//Ordenando a lista de pares pelas duas economias.
	std::sort(pairsList.begin(), pairsList.end(), comparePair);

	




	/*********************************************** Procedimento sequencial *****************************************************/
	
	//Vetor informado os nós já visitados.
	bool visited[V];

	for(auto i(0); i < V; i++){
		visited[i] = false;
	}

	//Tempo de ciclo para uma rota.
	double cicleTime = 0;

	//Distancia total da rota.
	double sumRoute = 0;

	/*
	routes[0].push_back(0);
	routes[0].push_back(pairsList[0].leftVertex);
	routes[0].push_back(pairsList[0].rightVertex);
	routes[0].push_back(0);
	*/

	//Tempo inicial da rota.
	cicleTime = getRouteDistance(0)/30.0 + getNumberOfStops(0)*1.5;

	//Peso total do veiculo na rota.
	double pesoTotal = getWeight(0);
	
	//1 para primeira interação de cada rota, 2 senão.
	int caso;
	for(auto i(0); i < numberOfBus; i++){
		for(auto it = pairsList.begin(); it < pairsList.end(); it++){
			/*if((std::find(routes[i].begin(), routes[i].end(), it->leftVertex) != routes[i].end() or
			   (std::find(routes[i].begin(), routes[i].end(), it->rightVertex)) != routes[i].end()) and
			   not (visited[it->leftVertex] or visited[it->rightVertex])*/

			if(it == pairsList.begin()){
				if(visited[it->leftVertex] == false and visited[it->rightVertex == false]){
					routes[i].push_back(0);
					routes[i].push_back(it->leftVertex);
					routes[i].push_back(it->rightVertex);
					routes[i].push_back(0);
				}
			
			}else{

				if(visited[it->leftVertex] == true and visited[it->rightVertex == false]){
					routes[i].insert(routes[i].end() + 1, visited[it->rightVertex]);
				}

				if(visited[it->leftVertex] == false and visited[it->rightVertex == true]){
					routes[i].insert(routes[i].end() - 2, visited[it->leftVertex]);
				}	
			}
		}	
	}



}