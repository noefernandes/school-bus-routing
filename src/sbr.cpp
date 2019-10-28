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

/*bool SBR::cicleTimeIsCorrect(int i){
	std::vector<int> newRoute = routes[i];


}
*/

double SBR::getRouteDistance(int i){
	double sumRoute = 0;
	for(unsigned int j(0); j < routes[i].size() - 1; j++){
		sumRoute += m[routes[i][j]][routes[i][j+1]];
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

	for(unsigned int j(0); j < routes[i].size() - 2; j++){
		pesoTotal += C[routes[i][j+1] - 1];
		//std::cout << pesoTotal;
	}

	return pesoTotal;
}

bool SBR::weightIsCorrect(double weightTotal, int vertex, int i){
	std::vector<int> temp(routes[i].size());
	std::copy(routes[i].begin(), routes[i].end(), temp.begin());
	double pesoTotal = 0;

	temp.insert(temp.begin() + 1, vertex);

	for(unsigned int j(0); j < temp.size() - 2; j++){
		pesoTotal += C[temp[j+1] - 1];
	}	

	return pesoTotal <= 1000;
}

bool SBR::cicleTimeIsCorrect(double cicleTime, int vertex, int mode, int i){
	std::vector<int> temp(routes[i].size());
	std::copy(routes[i].begin(), routes[i].end(), temp.begin());
	double sumRoute = 0;
	int stops = -1;

	if(mode == 1){
		temp.insert(temp.begin() + 1, vertex);
	}else{
		temp.insert(temp.end() - 2, vertex);
	}

	for(unsigned int j(0); j < temp.size() - 1; j++){
		sumRoute += m[temp[j]][temp[j+1]];
	}
		
	for(unsigned int j(0); j < temp.size() - 1; j++){
		stops++;
	}

	return sumRoute/30.0 + stops*1.5 <= 8.0;
}

void SBR::clarkeAndWright(void){
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
	
	
	bool visited[V];

	for(auto i(0); i < V; i++){
		visited[i] = false;
	}


	for(auto i(0); i < numberOfBus; i++){
		std::vector<Pair>::iterator it = pairsList.begin();
		while(not (visited[it->leftVertex] == false and visited[it->rightVertex] == false)){
			it++;
		}
		
		routes[i].push_back(0);
		routes[i].push_back(it->leftVertex);
		routes[i].push_back(it->rightVertex);
		routes[i].push_back(0);

		visited[it->rightVertex] = true;
		visited[it->leftVertex] = true;
		//std::cout << it->leftVertex << " " << it->rightVertex << "\n";
		pairsList.erase(it);
		double cicleTime = 0;
		double weightTotal = 0; 

		for(it = pairsList.begin(); it != pairsList.end(); it++){
			cicleTime = getRouteDistance(i)/30.0 + getNumberOfStops(i)*1.5;
			weightTotal = getWeight(i);
			if(visited[it->leftVertex] == false and visited[it->rightVertex] == false){
				continue;
			}

			if(visited[it->leftVertex] == true and visited[it->rightVertex] == true){
				continue;
			}

		
			if(routes[i][1] == it->leftVertex and cicleTimeIsCorrect(cicleTime, it->rightVertex, 1, i) and 
			weightIsCorrect(weightTotal, it->rightVertex, i) and visited[it->leftVertex]){
				routes[i].insert(routes[i].begin() + 1, it->rightVertex);
				visited[it->rightVertex] = true;
				//std::cout << it->leftVertex << " " << it->rightVertex << "\n"; 
				pairsList.erase(it);
			}

			if(routes[i][1] == it->rightVertex and cicleTimeIsCorrect(cicleTime, it->leftVertex, 1, i) and
			weightIsCorrect(weightTotal, it->leftVertex, i) and visited[it->rightVertex]){
				routes[i].insert(routes[i].begin() + 1, it->leftVertex);
				visited[it->leftVertex] = true;
				//std::cout << it->leftVertex << " " << it->rightVertex << "\n";
				pairsList.erase(it);
			}

			if(routes[i][routes[i].size() - 1] == it->leftVertex and cicleTimeIsCorrect(cicleTime, it->rightVertex, 2, i) and
			weightIsCorrect(weightTotal, it->rightVertex, i) and visited[it->leftVertex]){
				routes[i].insert(routes[i].end() - 2, it->rightVertex);
				visited[it->rightVertex] = true;
				//std::cout << it->leftVertex << " " << it->rightVertex << "\n";
				pairsList.erase(it);
			}

			if(routes[i][routes[i].size() - 1] == it->rightVertex and cicleTimeIsCorrect(cicleTime, it->leftVertex, 2, i) and
			weightIsCorrect(weightTotal, it->leftVertex, i) and visited[it->rightVertex]){
				routes[i].insert(routes[i].end() - 2, it->leftVertex);
				visited[it->leftVertex] = true;
				//std::cout << it->leftVertex << " " << it->rightVertex << "\n";
				pairsList.erase(it);
			}
		
		}	
	}

	std::cout << "Roteiro 1: "; 
	for(unsigned int j(0); j < routes[0].size(); j++){
		std::cout << routes[0][j] << " ";
	}

	std::cout << "\n";

	std::cout << "Peso: " << getWeight(0) << "\n";
	std::cout << "Distancia: " << getRouteDistance(0) << "\n";
	
	std::cout << "\n";
	std::cout << "Roteiro 2: ";

	for(unsigned int j(0); j < routes[1].size(); j++){
		std::cout << routes[1][j] << " ";
	}

	std::cout << "\n";
	std::cout << "Peso: " << getWeight(1) << "\n";
	std::cout << "Distancia: " << getRouteDistance(1) << "\n";

	std::cout << "\n";
	std::cout << "Roteiro 3: ";

	for(unsigned int j(0); j < routes[2].size(); j++){
		std::cout << routes[2][j] << " ";
	}

	std::cout << "\n";
	std::cout << "Peso: " << getWeight(2) << "\n";
	std::cout << "Distancia: " << getRouteDistance(2) << "\n";

	std::cout << "\n";
}