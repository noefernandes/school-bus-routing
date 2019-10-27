#include "sbr.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <bits/stdc++.h> 

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

	std::sort(pairsList.begin(), pairsList.end(), comparePair);

	for(unsigned int i(0); i < pairsList.size(); i++){
		std::cout << pairsList[i].saved << " " << pairsList[i].leftVertex << " " << pairsList[i].rightVertex << std::endl;
	}
}