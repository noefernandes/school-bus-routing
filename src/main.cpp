#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <utility>
#include <cmath>
#include "sbr.h"

int distance(std::pair<int,int> lhs, std::pair<int,int> rhs)
{
	return (int) std::floor(std::sqrt(std::pow(rhs.first - lhs.first, 2) + std::pow(rhs.second - rhs.second, 2)));
}

void loadGraph(std::string filename, std::ofstream & OutputFile)
{
	// Stream para ler o arquivo de entrada atual
	std::fstream File(filename);
	// String para descartar as partes não desejadas do arquivo de entrada
	std::cout << "O arquivo de saída abriu? " << OutputFile.is_open() << std::endl;
	std::cout << "O arquivo de entrada abriu? " << File.is_open() << std::endl;

	std::string dummy;
	// Ignorando partes denecessárias do arquivo de entrada
	std::getline(File,dummy);
	std::getline(File, dummy);
	std::getline(File, dummy);
	std::getline(File, dummy);

	std::string buffer;
	std::stringstream oss(dummy);

	oss >> buffer;
	buffer.clear();
	oss >> buffer;
	buffer.clear();
	oss >> buffer;

	int tamGrafo = std::stoi(buffer);

	buffer.clear();

	std::getline(File, dummy);

	oss.clear();
	oss.str(dummy);

	oss >> buffer;
	buffer.clear();
	oss >> buffer;
	buffer.clear();
	oss >> buffer;
	buffer.clear();
	oss >> buffer;

	int tamFrota = std::stoi(buffer);

	buffer.clear();

	std::getline(File, dummy);
	std::getline(File, dummy);

	oss.clear();
	oss.str(dummy);

	oss >> buffer;
	buffer.clear();
	oss >> buffer;
	buffer.clear();
	oss >> buffer;

	int capacidade = std::stoi(buffer);

	std::cout << "Tamanho do grafo: " << tamGrafo << "\nNúmero de ônibus disponíveis: " << tamFrota << "\nCapacidade dos onibus: " << capacidade << std::endl << std::endl;
	OutputFile << "Tamanho do grafo: " << tamGrafo << "\nNúmero de ônibus disponíveis: " << tamFrota << "\nCapacidade dos onibus: " << capacidade << std::endl << std::endl;

	SBR sbr(tamGrafo, capacidade, tamFrota);

	std::getline(File, dummy);
	std::vector<std::pair<int, int>> pairVector;
	//std::cout << "Fui Comparar o dummy" << std::endl;
	while(dummy.compare("DEMAND_SECTION ") != 0)
	{
		std::pair<int,int> par;
		int x,y;

		std::getline(File, dummy);
		oss.clear();
		oss.str(dummy);
		buffer.clear();

		oss >> buffer;
		buffer.clear();
		oss >> x;
		oss >> y;
		
		par = std::make_pair(x,y);
		pairVector.push_back(par);
	}
	//std::cout << "Acabei o vector"<<std::endl;

	for(unsigned int i{0}; i < pairVector.size()-1; i++)
	{
		for(unsigned int j{i+1}; j < pairVector.size()-1; j++)
		{
			//std::cout << "x1 = (" << pairVector[i].first << "/" << pairVector[i].second << ") x2 = (" << pairVector[j].first << "/" << pairVector[j].second  << ")"<< std::endl;
			sbr.insertEdge(i, j, distance(pairVector[i], pairVector[j]));
		}	
	}	
	//std::cout << "Acabei de ler os vértices" << std::endl;;

	sbr.loadVertexWeight(File);

	sbr.clarkeAndWright(OutputFile);

	File.close();
}

int main(){

	std::vector<std::string> n = {"n32", "n33", "n33", "n34", "n36", "n37", "n37", "n38", "n39", "n39", "n44"};
	std::vector<std::string> k = {"k5", "k5", "k6", "k5", "k5", "k5", "k6", "k5", "k5", "k6", "k6"}; 

	for(unsigned int i{0}; i < n.size(); i++)
	{
		std::string filenameFinal;
		filenameFinal = "Tests/Results/Resultado da Inst_A-" + n[i] + "-" + k[i] + ".txt";
		std::ofstream OutputFile(filenameFinal);

		std::cout << "Iniciando os testes: -----------------------" << std::endl;
		OutputFile << "Iniciando os testes: -----------------------" << std::endl;
		std::cout << "Instância " << i+1 << std::endl << std::endl;
		OutputFile << "Instância " << i+1 << std::endl << std::endl;

		std::string filenameInstance;

		filenameInstance = "Tests/Instances/A-" + n[i] + "-" + k[i] + ".vrp";

		loadGraph(filenameInstance, OutputFile);

		OutputFile.close();
	}

	return 0;
}