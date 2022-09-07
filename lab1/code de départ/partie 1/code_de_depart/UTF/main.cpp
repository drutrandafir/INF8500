///////////////////////////////////////////////////////////////////////////////
//
//	main.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include <systemc.h>
#include <Bubble.h>
#include <Reader.h>
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
	
	// Components
	Bubble iBubble("Bubble");
	Reader iReader("Reader");
	DataRAM iDataRAM( "DataRAM", "chiffre.hex", RAMSIZE, false );

	
	// Connections
	iReader.dataPortRAM(iDataRAM);
	iBubble.readPort(iReader);

	// D�marrage de l'application
	if (!m_bError)
	{
		cout << "Demarrage de la simulation." << endl;
		sc_start( -1, sc_core::sc_time_unit(sim_units) );
		cout << endl << "Simulation s'est terminee a " << sc_time_stamp() << " ns";
	}
	// Fin du programme
	return 0;
}
