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
  * @param[out] m_monitor is in int that holds the monitor display time
  *
  * @param[out] m_processor is in int that holds the processor cycle time
  *
  * @param[out] m_scanner is in int that holds the scanner cycle time
  *
  * @param[out] m_hdd is in int that holds the hard drive cycle time
  *
  * @param[out] m_keyboard is in int that holds the keyboard cycle time
  *
  * @param[out] m_memory is in int that holds the memory cycle time
  *
  * @param[out] m_projector is in int that holds the projector cycle time
  *
  * @param[out] m_logPath is a string that holds the log file path
  *
  * @param[out] m_logLocation is a string that determines the output locations
  *
  * @param[out] m_memType is a string that determines the system memory type
  *
  * @param[out] m_sysmemory is an integer that states the system memory size
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
        float version = 0;
        string path = "default.mdf";
        int monitor = 0;
        int processor = 0;
        int scanner = 0;
        int hdd = 0;
        int keyboard = 0;
        int memory = 0;
        int projector = 0;
        int sysMemory = 0;
        string logPath = "default.lgf";
        string logLocation = "Log to Monitor";
        string memType = "kbytes";
        string strInput;
        char temp;
        ifstream readIn;
        readIn.open( FILE );
        if( readIn.is_open() )
        {
            getline( readIn, strInput );      //read: Start
            getline( readIn, strInput, ':' ); //read: Version
            readIn >> version;
            getline(readIn, strInput, ':' );  //read: File Path
            readIn >> path;
            getline( readIn, strInput, ':' ); //read: Monitor
            readIn >> monitor;
            getline( readIn, strInput, ':' ); //read: Processor
            readIn >> processor;
            getline( readIn, strInput, ':' ); //read: Scanner
            readIn >> scanner;
            getline( readIn, strInput, ':' ); //read: Hard Drive
            readIn >> hdd;
            getline( readIn, strInput, ':' ); //read: Keyboard
            readIn >> keyboard;
            getline( readIn, strInput, ':' ); //read: Memory
            readIn >> memory;
            getline( readIn, strInput, ':' ); //read: Projector
            readIn >> projector;
            getline( readIn, strInput, '{' ); //read: System Memory Type
            getline( readIn, memType, '}' );
            getline( readIn, strInput, ':' ); //read: System Memory
            readIn >> sysMemory;
            getline( readIn, strInput, ':' ); //read: Log
            readIn.get( temp );
            getline( readIn, logLocation );
            if( logLocation == "Log to Monitor" )
            {
                logPath = "";
            }
            else if( logLocation == "Log to File" || logLocation == "Log to Both" ){
                getline( readIn, strInput, ':' );
                readIn >> logPath;
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

        config.m_version = version;
        config.m_path = path;
        config.m_monitor = monitor;
        config.m_processor = processor;
        config.m_scanner = scanner;
        config.m_hdd = hdd;
        config.m_keyboard = keyboard;
        config.m_memory = memory;
        config.m_projector = projector;
        config.m_sysMemory = sysMemory;
        config.m_memType = memType;
        config.m_logPath = logPath;
        config.m_logLocation = logLocation;

        return config;
    }
//