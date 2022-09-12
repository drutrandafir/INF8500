///////////////////////////////////////////////////////////////////////////////
//
//	Bubble.h
//
///////////////////////////////////////////////////////////////////////////////
#ifndef _BUBBLE_H_
#define _BUBBLE_H_

#include <systemc.h>
#include <stdio.h>
#include "InterfaceRead.h"


///////////////////////////////////////////////////////////////////////////////
//
//	Class Bubble
//
///////////////////////////////////////////////////////////////////////////////
class Bubble : public sc_module
{
public:
	// Ports    
	/*

	À compléter

	*/
	sc_in_clk clk;
	sc_out<unsigned int> address;
	sc_in<unsigned int> data;
	sc_out<bool> request;
	sc_in<bool> ack;

	// Constructor
	Bubble(sc_module_name zName);

	// Destructor
	~Bubble();

private:
	// Process SystemC
	SC_HAS_PROCESS(Bubble);

	enum readState {INIT, WAIT_NUM_VALUES, READ_NUM_VALUES, WAIT_VALUES, READ_VALUES, POST_READ_VALUES, SORT_VALUES};
	readState state = INIT;
	void method(void);
	void bubbleSort(unsigned int* ptr, int counter);

	bool isOrdered;
	int numValues = 0;
	unsigned int addr = 0x00;
	unsigned int* dataPtr;
	unsigned int itr = 0;
};

#endif