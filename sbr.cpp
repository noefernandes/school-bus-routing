#include "sbr.h"
#include <iostream>

int** SBR::getAdjacencyMatrix(void){
	return m;
}

void SBR::insertEdge(int a, int b){
	m[a][b] = 1;
	m[b][a] = 1;
}

void SBR::removeEdge(int a, int b){
	m[a][b] = 0;
	m[b][a] = 0;
}

void SBR::showGraph(void){
	for(auto i(0); i < V; i++){
		for(auto j(0); j < V; j++){
			std::cout << m[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
