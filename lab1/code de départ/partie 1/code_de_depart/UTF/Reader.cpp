///////////////////////////////////////////////////////////////////////////////
//
//	Reader.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "Reader.h"

///////////////////////////////////////////////////////////////////////////////
//
//	Constructor
//
///////////////////////////////////////////////////////////////////////////////
Reader::Reader(sc_module_name zName)
: sc_module(zName)
{
}

///////////////////////////////////////////////////////////////////////////////
//
//	Destructor
//
///////////////////////////////////////////////////////////////////////////////
Reader::~Reader()
{
}

///////////////////////////////////////////////////////////////////////////////
//
//	read
//
///////////////////////////////////////////////////////////////////////////////
unsigned int Reader::Read(unsigned int uiAddr)
{
	/*
	
	À compléter
	
	*/
	unsigned int value = dataPortRAM->Read(uiAddr);
	return value;
}
