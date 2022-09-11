///////////////////////////////////////////////////////////////////////////////
//
//	Reader.h
//
///////////////////////////////////////////////////////////////////////////////
#ifndef _READER_H_
#define _READER_H_

#include <systemc.h>
#include "LMBIF.h"
#include "InterfaceRead.h"

///////////////////////////////////////////////////////////////////////////////
//
//	Class Reader
//
///////////////////////////////////////////////////////////////////////////////
class Reader : public sc_module, public InterfaceRead
{
	public:
		// Ports
		/*
	
		À compléter
		
		*/
		sc_port<LMBIF> dataPortRAM;
		sc_in_clk clk;
		sc_in<unsigned int> address;
		sc_out<unsigned int> data;
		sc_in<bool> request;
		sc_out<bool> ack;
		
		// Constructor
		Reader( sc_module_name zName );

		// Destructor
		~Reader();

	private:
		// Process SystemC
		SC_HAS_PROCESS(Reader);
	
		// Read - InterfaceRead
		virtual void Read(void);
};

#endif
