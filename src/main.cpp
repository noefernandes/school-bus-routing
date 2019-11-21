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
	std::string dummy;
	// Ignorando partes denecessárias do arquivo de entrada
	std::getline(File,dummy);
	std::getline(File, dummy);
	std::getline(File, dummy);
	std::getline(File, dummy);

	// Criando a string que será utilizada para copiar os dados relevantes do arquivo
	std::string buffer;
	// Criando a stream que irá remover esses dados
	std::stringstream oss(dummy);

	// Pulando as strings e espaços até chegar no número de vértices do grafo
	oss >> buffer;
	buffer.clear();
	oss >> buffer;
	buffer.clear();
	oss >> buffer;

	// Coletando a quantidade de vértices do grafo do arquivo.
	int tamGrafo = std::stoi(buffer);

	buffer.clear();

	// Similar ao que fizemos com a quantidade de vértices, vamos coletar a quantidade de ônibus disponíveis para o problema
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

	//  Aqui pulamos uma linha irrelevante e preparamos a stream para ler os dados dos vértices do arquivo.
	std::getline(File, dummy);
	std::getline(File, dummy);

	oss.clear();
	oss.str(dummy);

	oss >> buffer;
	buffer.clear();
	oss >> buffer;
	buffer.clear();
	oss >> buffer;

	// Coletamos a capacidade de cada veículo
	int capacidade = std::stoi(buffer);

	// Inserimos no arquivo de resultado a configuração do grafo atual
	std::cout << "Tamanho do grafo: " << tamGrafo << "\nNúmero de ônibus disponíveis: " << tamFrota << "\nCapacidade dos onibus: " << capacidade << std::endl << std::endl;
	OutputFile << "Tamanho do grafo: " << tamGrafo << "\nNúmero de ônibus disponíveis: " << tamFrota << "\nCapacidade dos onibus: " << capacidade << std::endl << std::endl;

	// Criamos a estrutura que irá guardar as informações do grafo
	SBR sbr(tamGrafo, capacidade, tamFrota);

	std::getline(File, dummy);
	std::vector<std::pair<int, int>> pairVector;
	//std::cout << "Fui Comparar o dummy" << std::endl;
	// Percorremos o arquivo retirando as posições geográficas dos vértices para poder armazená-las no grafo
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

	// Aqui calculamos a distância entre o vértice i e j e inserimos ela no grafo, representando o peso da aresta (i,j)
	for(unsigned int i{0}; i < pairVector.size()-1; i++)
	{
		for(unsigned int j{i+1}; j < pairVector.size()-1; j++)
		{
			//std::cout << "x1 = (" << pairVector[i].first << "/" << pairVector[i].second << ") x2 = (" << pairVector[j].first << "/" << pairVector[j].second  << ")"<< std::endl;
			sbr.insertEdge(i, j, distance(pairVector[i], pairVector[j]));
		}	
	}	
	//std::cout << "Acabei de ler os vértices" << std::endl;;

	// Aqui chamamos a função que irá ler o peso dos vértices, que no nosso caso é a quantidade de alunos naquela parada.
	sbr.loadVertexWeight(File);

	// Chamamos o algoritmo do clarke & wright para encontrar a solução do problema
	sbr.clarkeAndWright(OutputFile);

	// Fechamos o arquivo
	File.close();
}

int main(){

	// Vetores com os "nomes" dos arquivos de teste, utilizado para ler todas as entradas
	std::vector<std::string> n = {"n32", "n33", "n33", "n34", "n36", "n37", "n37", "n38", "n39", "n39", "n44", "n45", "n45", "n46", "n48", "n53", "n54", "n55", "n60", "n61", "n62", "n63", "n63", "n64", "n65", "n69", "n80"};
	std::vector<std::string> k = {"k5", "k5", "k6", "k5", "k5", "k5", "k6", "k5", "k5", "k6", "k6", "k6", "k7", "k7", "k7", "k7", "k7", "k9", "k9", "k9", "k8", "k9", "k10", "k9", "k9", "k9", "k10"}; 

	// Aqui vamos ler todos os arquivos de teste e encontrar a solução para cada um, jogando essa solução num arquivo de "log" para ser analisado posteriormente
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