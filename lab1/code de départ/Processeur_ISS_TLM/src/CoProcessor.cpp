///////////////////////////////////////////////////////////////////////////////
//
//	CoProcessor.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "CoProcessor.h"
#include <iostream>
#include <vector>
using namespace std;


///////////////////////////////////////////////////////////////////////////////
//
//	Constructeur
//
///////////////////////////////////////////////////////////////////////////////
CoProcessor::CoProcessor( sc_module_name zName )
: sc_module(zName)
{
	SC_THREAD(thread);
	sensitive << ClockPort.pos();
		
	reg[0] = 0x0000;
	reg[1] = 0x0000;
	reg[2] = 0x0000;
	reg[3] = 0x0000;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Destructeur
//
///////////////////////////////////////////////////////////////////////////////
CoProcessor::~CoProcessor()
{
}


///////////////////////////////////////////////////////////////////////////////
//
//	thread
//
///////////////////////////////////////////////////////////////////////////////
void CoProcessor::thread(void)
{
	// Variables locales
	/*
		À compléter
	*/
	reg[0].write(0x0000);
	reg[2].write(0x0000);
	int itemCnt = 0;
	unsigned int* ptrData;

	// Boucle infinie
	while(1)
	{
		
	    // On attend une transaction 
		/*
			À compléter
		*/
		wait(CoProcessor_RW_OutPort.default_event());
		bool isRead = CoProcessor_RW_OutPort.read();

		// On s'assure qu'une donnée est valide (enable)
		/*
			À compléter
		*/
		wait(CoProcessor_Enable_InPort.default_event());
		if(CoProcessor_Enable_InPort.read() == false) return;

		//Lecture adresse
		/*
			À compléter
		*/			
		ulAddress = CoProcessor_Data_InPort.read();

		switch(ulAddress):
			// Write (du point de vue du processeur)
			/*
				À compléter. Selon l'adresse qui vient du processeur:
					- Lecture et stockage du nombre d'éléments à trier et 
					- lecture des éléments à trier
					- Tri (appel à bubbleSort)
					- Ne pas oublier d'utiliser les bons registres
			*/
			case 0x2000:
				reg[2].write(0x0000);
				CoProcessor_Ready_OutPort.write(true);
				wait(CoProcessor_Enable_InPort.default_event());

				unsigned int dataLength = CoProcessor_Data_InPort.read();
				reg[0].write(dataLength);
				ptrData = new unsigned int(dataLength);
				itemCnt = dataLength;

				CoProcessor_Enable_OutPort.write(false);
				break;

			case 0x2001:

				CoProcessor_Ready_OutPort.write(true);
				wait(CoProcessor_Enable_InPort.default_event());

				unsigned int item = CoProcessor_Data_InPort.read();
				ptrData[itemCnt - 1] = item;
				
				CoProcessor_Enable_OutPort.write(false);
				itemCnt--;

				if(itemCnt == 0){
					reg[2].write(0x0001);
					bubbleSort(ptrData, reg[0].read());
				}
				break;

		
			// Read (du point de vue du processeur)
			/*
				À compléter. Selon l'adresse qui vient du processeur:
					- Lecture du registre d'état du coprocesseur 
					- lecture du nombre d'éléments à envoyer au processeur
					- Lecture des élément triés
			*/
			case 0x2002:
				CoProcessor_Data_OutPort.write(reg[2].read());
				CoProcessor_Ready_OutPort.write(true);

				wait(CoProcessor_Enable_InPort.default_event());
				if(CoProcessor_Enable_InPort.read() == true) return;

				CoProcessor_Ready_OutPort.write(false);

			case 0x2003:
				CoProcessor_Data_OutPort.write(len(ptrData));
				CoProcessor_Ready_OutPort.write(true);

				wait(CoProcessor_Enable_InPort.default_event());
				if(CoProcessor_Enable_InPort.read() == true) return;
				
				CoProcessor_Ready_OutPort.write(false);

			case 0x2004:
				CoProcessor_Data_OutPort.write(len(ptrData[itemCnt]));
				CoProcessor_Ready_OutPort.write(true);

				wait(CoProcessor_Enable_InPort.default_event());
				if(CoProcessor_Enable_InPort.read() == true) return;
				
				CoProcessor_Ready_OutPort.write(false);
				itemCnt++;

	}
}


///////////////////////////////////////////////////////////////////////////////
//
//	bubbleSort
//
///////////////////////////////////////////////////////////////////////////////
void CoProcessor::bubbleSort(unsigned int *ptr, int n_elements)
{
	/*

		À compléter. Ne pas oublier de modifier l'état du bon registre du coprocesseur à la fin du traitement (voir énoncé)

	*/
	bool isOrdered = false;

		while (!isOrdered) {
			wait(ClockPort.pos_edge());
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
		reg[2].write(0x002);
}