///////////////////////////////////////////////////////////////////////////////
//
//	Bubble.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "Bubble.h"


///////////////////////////////////////////////////////////////////////////////
//
//	Constructeur
//
///////////////////////////////////////////////////////////////////////////////
Bubble::Bubble( sc_module_name zName )
: sc_module(zName)
{
	/*
	
	À compléter
	
	*/
	SC_THREAD(thread);
}


///////////////////////////////////////////////////////////////////////////////
//
//	Destructeur
//
///////////////////////////////////////////////////////////////////////////////
Bubble::~Bubble()
{
	/*
	
	À compléter
	
	*/
}


///////////////////////////////////////////////////////////////////////////////
//
//	thread
//
///////////////////////////////////////////////////////////////////////////////
void Bubble::thread(void)
{
	/*
	
	À compléter
	
	*/
	address.write(addr);
	request.write(true);

	do {
		wait(clk->posedge_event());
	} while (!ack.read());

	numValues = data.read();
	request.write(false);

	dataPtr = new unsigned int(numValues);

	// Lecture des éléments à trier
	for (int itr = 0; itr < numValues; itr++) {
		addr += 0x04;
		address.write(addr);
		request.write(true);

		do {
			wait(clk->posedge_event());
		} while (!ack.read());

		dataPtr[itr] = data.read();
		request.write(false);
	}
	
	bubbleSort(dataPtr, numValues);

	// Arrêt de la simulation
	sc_stop();

}


///////////////////////////////////////////////////////////////////////////////
//
//	bubbleSort
//
///////////////////////////////////////////////////////////////////////////////
void Bubble::bubbleSort(unsigned int *ptr, int counter)
{
	// Affichage avant tri
	/*

	À compléter

	*/
	printf("Avant: [");
	for (int itr = 0; itr < counter; itr++) {
		printf(" %u ", ptr[itr]);
	}
	printf("]\n\n");

	// Tri
	/*

	À compléter

	*/
	bool isOrdered = false;

	while (!isOrdered) {
		cout << endl << "Bubble Begin " << sc_time_stamp() << endl;
		wait(clk->posedge_event());
		isOrdered = true;
		for (int itr = 0; itr < (counter - 1); itr++) {
			if (ptr[itr] > ptr[itr + 1]) {
				unsigned int tmp = ptr[itr];
				ptr[itr] = ptr[itr + 1];
				ptr[itr + 1] = tmp;
				isOrdered = false;
			}
		}
		cout << "Bubble end " << sc_time_stamp() << endl;
	}

	// Affichage après tri
	/*

	À compléter

	*/
	printf("Apres: [");
	for (int itr = 0; itr < counter; itr++) {
		printf(" %u ", ptr[itr]);
	}
	printf("]\n\n");

	return;
}
