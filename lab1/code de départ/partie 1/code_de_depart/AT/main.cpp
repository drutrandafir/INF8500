///////////////////////////////////////////////////////////////////////////////
//
//	main.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include <systemc.h>
#include "Bubble.h"
#include "Reader.h"
#include "DataRAM.h"

#define RAMSIZE 0x400

// Global variables
bool m_bError = false;

///////////////////////////////////////////////////////////////////////////////
//
//	Main
//
///////////////////////////////////////////////////////////////////////////////
int sc_main(int arg_count, char **arg_value)
{
	// Variables
	int sim_units = 2; //SC_NS 
	
	// Instanciation des composants
	/*
	
	À compléter
	
	*/
	Reader iReader("Reader");
	Bubble iBubble("Bubble");
	DataRAM iDataRAM("DataRAM", "chiffre.hex", RAMSIZE, false);

	// Déclaration des signaux
	/*
	
	À compléter
	
	*/
	sc_buffer<unsigned int> bData;
	sc_buffer<unsigned int> bAddress;
	sc_buffer<bool> bAck;
	sc_buffer<bool> bRequest;
	sc_clock clk("clk");
	
	// Connexion des ports
	/*
	
	À compléter
	
	*/
	iReader.dataPortRAM(iDataRAM);
	iReader.data(bData);
	iReader.address(bAddress);
	iReader.ack(bAck);
	iReader.request(bRequest);
	iReader.clk(clk);

	iBubble.data(bData);
	iBubble.address(bAddress);
	iBubble.ack(bAck);
	iBubble.request(bRequest);
	iBubble.clk(clk);

	// Démarrage de l'application
	if (!m_bError)
	{
		cout << "Demarrage de la simulation." << endl;
		sc_start( -1, sc_core::sc_time_unit(sim_units) );
		cout << endl << "Simulation s'est terminee a " << sc_time_stamp() << " ns";
	}
	// Fin du programme
	return 0;
}
