#include <iostream>
#include "sbr.h"
int main(){

	SBR sbr(4);

	sbr.insertEdge(1,1);
	sbr.insertEdge(2,3);
	sbr.insertEdge(0,0);
	sbr.showGraph();
	return 0;
}