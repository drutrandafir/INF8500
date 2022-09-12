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
Bubble::Bubble(sc_module_name zName)
	: sc_module(zName)
{
	/*

	À compléter

	*/
	SC_METHOD(method);
	sensitive << clk.pos();
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
void Bubble::method(void)
{
	/*

	À compléter

	*/
	switch (state)
	{
	case INIT:
		address.write(addr);
		request.write(true);
		state = WAIT_NUM_VALUES;
		
		break;

	case WAIT_NUM_VALUES:
		if (ack.read())
		{
			state = READ_NUM_VALUES;
			break;
		}
		else
			break;

	case READ_NUM_VALUES:
		numValues = data.read();
		dataPtr = new unsigned int(numValues);
		request.write(false);
		state = POST_READ_VALUES;
		break;

	case POST_READ_VALUES:
		if (itr != numValues)
		{
			addr += 0x04;
			address.write(addr);
			request.write(true);
			state = WAIT_VALUES;
			break;
		}
		else
			printf("Avant: [");
			for (int iter = 0; iter < numValues; iter++) 
			{
				printf(" %u ", dataPtr[iter]);
			}
			printf("]\n\n");
			state = SORT_VALUES;
			break;

	case WAIT_VALUES:
		if (ack.read())
		{
			state = READ_VALUES;
			break;
		}
		else
			break;

	case READ_VALUES:
		dataPtr[itr] = data.read();
		request.write(false);
		itr++;
		state = POST_READ_VALUES;
		break;

	case SORT_VALUES:
		bubbleSort(dataPtr, numValues);
		if (isOrdered == false)
		{
			state = SORT_VALUES;
			break;
		}
		else
		{
			printf("Apres: [");
			for (int iter = 0; iter < numValues; iter++) {
				printf(" %u ", dataPtr[iter]);
			}
			printf("]\n\n");

			// Arrêt de la simulation
			sc_stop();
		}
	}
}


///////////////////////////////////////////////////////////////////////////////
//
//	bubbleSort
//
///////////////////////////////////////////////////////////////////////////////
void Bubble::bubbleSort(unsigned int* ptr, int counter)
{
	// Tri
	/*

	À compléter

	*/
	isOrdered = true;
	cout << endl << "Bubble Begin " << sc_time_stamp() << endl;
	for (int itr = 0; itr < (counter - 1); itr++) {
		if (ptr[itr] > ptr[itr + 1]) {
			unsigned int tmp = ptr[itr];
			ptr[itr] = ptr[itr + 1];
			ptr[itr + 1] = tmp;
			isOrdered = false;
		}
	}
	cout << "Bubble end " << sc_time_stamp() << endl;


	// Affichage après tri
	/*

	À compléter

	*/
	return;
}