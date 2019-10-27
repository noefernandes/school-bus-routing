#include <iostream>
#include "sbr.h"
int main(){

	SBR sbr(11);

	sbr.insertEdge(0, 1, 24.1);
	sbr.insertEdge(0, 2, 3.8);
	sbr.insertEdge(0, 3, 7.2);
	sbr.insertEdge(0, 4, 5.3);
	sbr.insertEdge(0, 5, 15.1);
	sbr.insertEdge(0, 6, 17.1);
	sbr.insertEdge(0, 7, 6.8);
	sbr.insertEdge(0, 8, 7.2);
	sbr.insertEdge(0, 9, 11.9);
	sbr.insertEdge(0, 10, 10.8);

	sbr.insertEdge(1, 2, 20.9);
	sbr.insertEdge(1, 3, 20.6);
	sbr.insertEdge(1, 4, 20.1);
	sbr.insertEdge(1, 5, 33.1);
	sbr.insertEdge(1, 6, 9.5);
	sbr.insertEdge(1, 7, 21.7);
	sbr.insertEdge(1, 8, 17.3);
	sbr.insertEdge(1, 9, 18.8);
	sbr.insertEdge(1, 10, 15.3);

	sbr.insertEdge(2, 3, 4.4);
	sbr.insertEdge(2, 4, 4.0);
	sbr.insertEdge(2, 5, 17.5);
	sbr.insertEdge(2, 6, 12.7);
	sbr.insertEdge(2, 7, 6.4);
	sbr.insertEdge(2, 8, 5.2);
	sbr.insertEdge(2, 9, 12.8);
	sbr.insertEdge(2, 10, 7.9);

	sbr.insertEdge(3, 4, 7.2);
	sbr.insertEdge(3, 5, 21.2);
	sbr.insertEdge(3, 6, 14.4);
	sbr.insertEdge(3, 7, 10.2);
	sbr.insertEdge(3, 8, 7.8);
	sbr.insertEdge(3, 9, 12.0);
	sbr.insertEdge(3, 10, 10.5);

	sbr.insertEdge(4, 5, 14.7);
	sbr.insertEdge(4, 6, 12.4);
	sbr.insertEdge(4, 7, 4.1);
	sbr.insertEdge(4, 8, 4.0);
	sbr.insertEdge(4, 9, 6.4);
	sbr.insertEdge(4, 10, 8.3);

	sbr.insertEdge(5, 6, 27.6);
	sbr.insertEdge(5, 7, 13.3);
	sbr.insertEdge(5, 8, 17.1);
	sbr.insertEdge(5, 9, 16.9);
	sbr.insertEdge(5, 10, 21.3);

	sbr.insertEdge(6, 7, 15.2);
	sbr.insertEdge(6, 8, 10.9);
	sbr.insertEdge(6, 9, 14.0);
	sbr.insertEdge(6, 10, 9.3);

	sbr.insertEdge(7, 8, 4.6);
	sbr.insertEdge(7, 9, 4.2);
	sbr.insertEdge(7, 10, 8.2);

	sbr.insertEdge(8, 9, 5.9);
	sbr.insertEdge(8, 10, 4.5);

	sbr.insertEdge(9, 10, 4.6);

	//sbr.showGraph();

	//sbr.loadStudentsPerStop("paradas.txt");
	//sbr.showStudentsPerStop();
	sbr.clarkeAndWright();

	return 0;
}