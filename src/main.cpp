#include <iostream>
#include "sbr.h"
int main(){

	SBR sbr(7);

	sbr.insertEdge(1, 1, 12);
	sbr.insertEdge(1, 3, 5);
	sbr.insertEdge(1, 6, 11);
	sbr.insertEdge(1, 4, 9);
	sbr.insertEdge(2, 3, 15);
	sbr.insertEdge(0, 0, 3);
	sbr.insertEdge(3, 3, 10);
	sbr.showGraph();

	sbr.loadStudentsPerStop("paradas.txt");
	sbr.showStudentsPerStop();

	return 0;
}