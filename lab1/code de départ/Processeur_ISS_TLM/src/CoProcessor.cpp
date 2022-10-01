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
	int itemCnt = 0;
	unsigned int dataLength = 0;
	unsigned int ulAddress = 0;
	unsigned int* ptrData;
	unsigned int* outData = (unsigned int*) malloc(sizeof(unsigned int));

	// Boucle infinie
	while(1)
	{
		
	    // On attend une transaction 
		/*
			À compléter
		*/
		wait(CoProcessor_RW_OutPort.default_event());

		// On s'assure qu'une donnée est valide (enable)
		/*
			À compléter
		*/
		if(CoProcessor_Enable_InPort.read() == false) return;

		//Lecture adresse
		/*
			À compléter
		*/			
		ulAddress = CoProcessor_Data_InPort.read();

		switch(ulAddress) {
			// Write (du point de vue du processeur)
			/*
				À compléter. Selon l'adresse qui vient du processeur:
					- Lecture et stockage du nombre d'éléments à trier et 
					- lecture des éléments à trier
					- Tri (appel à bubbleSort)
					- Ne pas oublier d'utiliser les bons registres
			*/
			case 0x2000:
				{
					// Prêt pour les données
					reg[2] = (0x0000);
					CoProcessor_Ready_OutPort.write(true);
					wait(CoProcessor_Enable_InPort.default_event());

					// Lire la taille des données
					dataLength = CoProcessor_Data_InPort.read();
					reg[0] = (dataLength);
					ptrData = new unsigned int(dataLength);

					CoProcessor_Ready_OutPort.write(false);
					break;
				}

			case 0x2001:
				{
					// Prêt pour les données
					CoProcessor_Ready_OutPort.write(true);
					wait(CoProcessor_Enable_InPort.default_event());

					// Sauvegarde des données, incrémentation du compteur
					unsigned int item = CoProcessor_Data_InPort.read();
					ptrData[itemCnt] = item;
					itemCnt++;
					
					CoProcessor_Ready_OutPort.write(false);

					/* Si le compteur atteint la valeur reçue de la taille des données,
					   on débute le triage */
					if(itemCnt >= reg[0]){
						reg[2].write(0x0001);
						bubbleSort(ptrData, reg[0]);
						itemCnt = 0;
					}
					break;
				}

		
			// Read (du point de vue du processeur)
			/*
				À compléter. Selon l'adresse qui vient du processeur:
					- Lecture du registre d'état du coprocesseur 
					- lecture du nombre d'éléments à envoyer au processeur
					- Lecture des élément triés
			*/
			case 0x2002:
				{	
					// Écriture de l'état
					outData[0] = reg[2];
					CoProcessor_Data_OutPort.write(outData[0]);
					CoProcessor_Ready_OutPort.write(true);

					wait(CoProcessor_Enable_InPort.default_event());

					CoProcessor_Ready_OutPort.write(false);
					break;
				}

			case 0x2003:
				{
					// Écriture de la taille du tableau
					CoProcessor_Data_OutPort.write(dataLength);
					CoProcessor_Ready_OutPort.write(true);

					wait(CoProcessor_Enable_InPort.default_event());
					if(CoProcessor_Enable_InPort.read() == true) return;
					
					CoProcessor_Ready_OutPort.write(false);
					break;
				}

			case 0x2004:
				{
					// Écriture d'un élément du tableau à un index incrémenté à chaque appel
					CoProcessor_Data_OutPort.write(ptrData[itemCnt]);
					CoProcessor_Ready_OutPort.write(true);
					itemCnt++;

					wait(CoProcessor_Enable_InPort.default_event());
					if(CoProcessor_Enable_InPort.read() == true) return;
					
					CoProcessor_Ready_OutPort.write(false);

					break;
				}

			default:
				break;
		}

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
		wait();
		isOrdered = true;
		for (int itr = 0; itr < (n_elements - 1); itr++) {
			if (ptr[itr] > ptr[itr + 1]) {
				unsigned int tmp = ptr[itr];
				ptr[itr] = ptr[itr + 1];
				ptr[itr + 1] = tmp;
				isOrdered = false;
			}
		}
	}

	reg[2] = (0x002);
}