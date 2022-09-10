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
	// Variable
	int numValues = 0;
	unsigned int addr = 0x00;
	unsigned int* dataPtr;
	
	// 1ere lecture: nombre d'éléments à trier
	/*
	
	À compléter
	
	*/
	numValues = readPort->Read(addr);
	dataPtr = new unsigned int(numValues);

	// Lecture des éléments à trier
	/*
	
	À compléter
	
	*/
	for (int itr = 0; itr < numValues; itr++) {
		addr += 0x04;
		dataPtr[itr] = readPort->Read(addr);
	}

	//Appel à bubble sort
	/*
	
	À compléter
	
	*/
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
		isOrdered = true;
		for (int itr = 0; itr < (counter - 1); itr++) {
			if (ptr[itr] > ptr[itr + 1]) {
				unsigned int tmp = ptr[itr];
				ptr[itr] = ptr[itr + 1];
				ptr[itr + 1] = tmp;
				isOrdered = false;
			}
		}
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
