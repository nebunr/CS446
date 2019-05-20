// Class Implementation File Information ////
/**
  * @file Config.cpp
  *
  * @brief Implementation file for Config class
  *
  * @details Implements all multiline member methods of the Config class
  *
  * @verion 1.00
  *		Benjamin Estela (9 February 2019)
  *		Initial development
  *
  *	@version 1.01
  *		Benjamin Estela (13 March 2019)
  *		Inclusion of m_memType and m_sysMemory
  *
  * @version 1.02
  *		Benjamin Estela (31 March 2019)
  *		Inclusion of block memory and projector and hdd count
  *
  * @version 1.03
  *     Benjamin Estela (22 April 2019)
  *     Inclusion of quantum and schedule
  *
  * @note Requires Config.h
  */
//
// Header Files ////
//
    #include <iostream>
    #include <fstream>
    #include "Config.h"
    using namespace std;
//
// Class/Data Structure Member Implementation ////
//
/**
  * @brief Config default class constructor
  *
  * @details Sets every private variable to 0 or to an empty string
  *
  * @param[out] m_version is a float that holds the version
  *
  * @param[out] m_path is a string that holds the path for the meta data
  *
  * @param[out] m_monitor is an int that holds the monitor display time
  *
  * @param[out] m_processor is an int that holds the processor cycle time
  *
  * @param[out] m_scanner is an int that holds the scanner cycle time
  *
  * @param[out] m_hdd is an int that holds the hard drive cycle time
  *
  * @param[out] m_keyboard is an int that holds the keyboard cycle time
  *
  * @param[out] m_memory is an int that holds the memory cycle time
  *
  * @param[out] m_projector is an int that holds the projector cycle time
  *
  * @param[out] m_logPath is a string that holds the log file path
  *
  * @param[out] m_logLocation is a string that determines the output locations
  *
  * @param[out] m_memType is a string that determines the system memory type
  *
  * @param[out] m_sysmemory is an integer that states the system memory size
  *
  * @param[out] m_quantum is an integer holding the processor quantum number
  *
  * @param[out] m_schedule is a string holding the cpu scheduling format
  *
  * @return None
  *
  * @note Config class constructor
  */
    Config::Config()
    {
        m_version = 0;
        m_path = "";
        m_monitor = 0;
        m_processor = 0;
        m_scanner = 0;
        m_hdd = 0;
        m_keyboard = 0;
        m_memory = 0;
        m_projector = 0;
        m_memType = "";
        m_sysMemory = 0;
        m_logPath = "";
        m_logLocation = "";
        m_quantum = 0;
        m_schedule = "";
    }
/**
 * @brief The config file is read in then the meta data file is read in
 *
 * @details The config class is setup with proper values found in the file,
 *          this allows for proper calculations with the meta data in the
 *          function call at the end
 *
 * @exception Boundary
 *              if config file cannot be opened, an error is shown
 *
 * @exception Boundary
 *              if logLocation is invalid, an error is shown
 *
 * @param[in] FILE is the file directory that holds the configuration file
 *
 * @param[in] config is the class that will hold the configuration data
 *          for the meta data to eventually use
 *
 * @return config is defined with potentially new values
 *
 * @note none
 */
    Config Config::readConfig( const char* FILE, Config config )
    {
        string strInput;
        char temp;
        ifstream readIn;
        readIn.open( FILE );
        if( readIn.is_open() )
        {
            getline( readIn, strInput );      //read: Start
            getline( readIn, strInput, ':' ); //read: Version
            readIn >> config.m_version;
            getline(readIn, strInput, ':' );  //read: File Path
            readIn >> config.m_path;
            getline( readIn, strInput, ':');  //read: Processor Quantum Number
            readIn >> config.m_quantum;
            getline( readIn, strInput, ':');  //read: CPU Scheduling
            readIn >> config.m_schedule;
            getline( readIn, strInput, ':' ); //read: Processor
            readIn >> config.m_processor;
            getline( readIn, strInput, ':' ); //read: Monitor
            readIn >> config.m_monitor;
            getline( readIn, strInput, ':' ); //read: Hard Drive
            readIn >> config.m_hdd;
            getline( readIn, strInput, ':' ); //read: Projector
            readIn >> config.m_projector;
            getline( readIn, strInput, ':' ); //read: Keyboard
            readIn >> config.m_keyboard;
            getline( readIn, strInput, ':' ); //read: Memory
            readIn >> config.m_memory;
            getline( readIn, strInput, ':' ); //read: Scanner
            readIn >> config.m_scanner;
            getline( readIn, strInput, '{' ); //read: System Memory Type
            getline( readIn, config.m_memType, '}' );
            getline( readIn, strInput, ':' ); //read: System Memory
            readIn >> config.m_sysMemory;
            getline( readIn, strInput, '{' ); //read: Memory Block Type
            getline( readIn, config.m_blockType, '}' );
            getline( readIn, strInput, ':' ); //read: Memory Block
            readIn >> config.m_blockMemory;
            getline( readIn, strInput, ':' ); //read: Projector Quantity
            readIn >> config.m_projectorCount;
            getline( readIn, strInput, ':' ); //read: Hard Drive Quantity
            readIn >> config.m_hddCount;
            getline( readIn, strInput, ':' ); //read: Log
            readIn.get( temp );
            getline( readIn, config.m_logLocation );
            if( config.m_logLocation == "Log to Monitor" )
            {
                config.m_logPath = "";
            }
            else if( config.m_logLocation == "Log to File"
                  || config.m_logLocation == "Log to Both" ){
                getline( readIn, strInput, ':' );
                readIn >> config.m_logPath;
            }
            else
            {
                cout << "No log file destination." << endl << endl;
            }
        }
        else
        {
            cout << "Could not open config file." << endl;
        }
        readIn.close();
        return config;
    }
//