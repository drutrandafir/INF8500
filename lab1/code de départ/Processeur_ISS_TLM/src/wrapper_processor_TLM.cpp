///////////////////////////////////////////////////////////////////////////////
//
//	wrapper_processor_TLM.cpp
//
///////////////////////////////////////////////////////////////////////////////
#include "wrapper_processor_TLM.h"


///////////////////////////////////////////////////////////////////////////////
//
//	Constructeur
//
///////////////////////////////////////////////////////////////////////////////
wrapper_processor_TLM::wrapper_processor_TLM(sc_module_name zName, bool bVerbose)
: sc_module(zName)
{
	// Thread
	SC_THREAD( thread );
	sensitive << ClockPort.pos();

	// Initialisation
	m_bVerbose = bVerbose;
}


///////////////////////////////////////////////////////////////////////////////
//
//	Destructeur
//
///////////////////////////////////////////////////////////////////////////////
wrapper_processor_TLM::~wrapper_processor_TLM()
{
	
}


///////////////////////////////////////////////////////////////////////////////
//
//	Thread
//
///////////////////////////////////////////////////////////////////////////////
void wrapper_processor_TLM::thread()
{
	// Variable
	unsigned long ulDestinationAddress;
	unsigned int ulData;
	
	// Boucle
	while(1)
	{
	
		// Le wrapper est prêt
		Wrapper_Ready_OutPort.write( true );

        // On attend une transaction 
		do {
			wait(Wrapper_Enable_InPort.default_event());
		}while(Wrapper_Enable_InPort.read() == false);

		// Écriture
		if(Wrapper_RW_InPort.read() == false)
		{
			// Occupé
			Wrapper_Ready_OutPort.write( false );
			
			// Récupère les données
			ulData = Wrapper_Data_InPort.read();
			ulDestinationAddress = Wrapper_Address_InPort.read();
						
			// écriture sur le bus
			busLT_write(ulDestinationAddress, (void*)&ulData, sizeof(unsigned int));
		}
		
		// Lecture
		else /* Wrapper_RW_InPort.read() == true */
		{
			/*
				À compléter. S'inspirer de l'écriture.
			*/
		    Wrapper_Ready_OutPort.write(false);

			unsigned int *ptrData = (unsigned int*) malloc(sizeof(unsigned int));
			ulDestinationAddress = Wrapper_Address_InPort.read();

			busLT_read(ulDestinationAddress, ptrData, sizeof(ptrData));

			Wrapper_Data_OutPort.write(*ptrData);
			
		}
	}
	
}


///////////////////////////////////////////////////////////////////////////////
//
//	busLT_write
//
///////////////////////////////////////////////////////////////////////////////
bool wrapper_processor_TLM::busLT_write(unsigned long ulAddress,  void* ptrData, unsigned long ulDataLength)
{
	tlm::tlm_command cmd = tlm::TLM_WRITE_COMMAND;
	tlm::tlm_generic_payload* trans = new tlm::tlm_generic_payload;
	sc_time delay = sc_time(40, SC_NS);
	
	// Création Requête
	trans->set_command( cmd );
	trans->set_address( ulAddress );
	trans->set_data_length( ulDataLength );
	trans->set_streaming_width( ulDataLength ); // = data_length to indicate no streaming
	trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
	trans->set_dmi_allowed( false ); // Mandatory initial value
	trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

		if(ulDataLength > DATA_TRANSACTION_SIZE)
		{
			for(unsigned int i = 0; i < ulDataLength; i+=DATA_TRANSACTION_SIZE)
			{
				trans->set_data_ptr( reinterpret_cast<unsigned char*>((char*)(ptrData) + i) );
				socket->b_transport( *trans, delay );
				
				// Initatior verifie la réponse
				if ( trans->is_response_error() )
				{
					SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
					return false;
				}
				wait(delay);
			}
		}
		else
		{
			trans->set_data_ptr( reinterpret_cast<unsigned char*>(ptrData) );
			socket->b_transport( *trans, delay ); 
			
			// Initatior verifie la réponse			
			if ( trans->is_response_error() )
			{
				SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
				return false;
			}
			wait(delay);
		}
		
	return true;
}

//////////////////////////////////////////////////////////////////////////////
/// 
/// busLT_read
///
//////////////////////////////////////////////////////////////////////////////
bool wrapper_processor_TLM::busLT_read(unsigned long ulAddress,  void* ptrData, unsigned long ulDataLength)
{	  
  	
    command_type cmd = tlm::TLM_READ_COMMAND;
	transaction_type* trans = new transaction_type;
	sc_time delay = sc_time(0.0005, SC_NS);
	
	// Création Requête
	trans->set_address( ulAddress );
	trans->set_command( cmd );
	trans->set_data_ptr( reinterpret_cast<unsigned char*>(ptrData) );
	trans->set_data_length( ulDataLength );
	trans->set_streaming_width( ulDataLength ); // = Data_length to indicate no streaming
	trans->set_byte_enable_ptr( 0 ); // 0 indicates unused
	trans->set_dmi_allowed( false ); // Mandatory initial value
	trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE ); // Mandatory initial value

	//Appelle bloquante
	socket->b_transport( *trans, delay );  

	// Initatior verifie la réponse
	if ( trans->is_response_error() )
	{
		SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
		return false;
	}

	// Delai estimé pour que la trasanction soit réalisée
	wait(delay);
	return true;
}
