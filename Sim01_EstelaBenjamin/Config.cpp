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
  * @note Requires Config.h, MetaData.cpp
  */
//
// Header Files ////
//
    #include <iostream>
    #include <fstream>
    #include "Config.h"
    #include "MetaData.cpp"
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
        m_logPath = "";
        m_logLocation = "";
    }
/**
  * @brief This function takes m_logLocation and converts the possible values
  *         into an int
  *
  * @details Depending on the log location, a different int value is returned,
  *         this is so a switch statement can be used in PrintMeta
  *
  * @exception Boundary
  *         if invalid m_logLocation, logDir is set to -1
  *
  * @param[in] m_logLocation is a string that determines the output locations
  *
  * @return logDir is an int that represents the output locations
  *
  * @note None
  */
    int Config::intLocation()
    {
        int logDir;
        if( m_logLocation == "Log to Monitor" )
        {
            logDir = 0;
        }
        else if( m_logLocation == "Log to File" )
        {
            logDir = 1;
        }
        else if( m_logLocation == "Log to Both" )
        {
            logDir = 2;
        }
        else
        {
            logDir = -1;
        }
        return logDir;
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
 * @note Calls MetaData within function
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
        string logPath = "default.lgf";
        string logLocation = "Log to Monitor";
        string strInput;
        char temp;
        bool logExists = false;
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
            getline( readIn, strInput, ':' ); //read: Log
            readIn.get( temp );
            getline( readIn, logLocation );
            if( logLocation == "Log to Monitor" )
            {
                cout << "Configuration File Data" << endl;
                cout << "Monitor = " << monitor << " ms/cycle" << endl;
                cout << "Processor = " << processor << " ms/cycle" << endl;
                cout << "Scanner = " << scanner << " ms/cycle" << endl;
                cout << "Hard Drive = " << hdd << " ms/cycle" << endl;
                cout << "Keyboard = " << keyboard << " ms/cycle" << endl;
                cout << "Memory = " << memory << " ms/cycle" << endl;
                cout << "Projector = " << projector << " ms/cycle" << endl;
                cout << "Logged to: monitor" << endl << endl;
                logPath = "";
            }
            else if( logLocation == "Log to File" )
            {
                cout << "Configuration File Data" << endl;
                getline( readIn, strInput, ':' );
                readIn >> logPath;
                cout << "Logged to: " << logPath << endl << endl;
                logExists = true;
            }
            else if( logLocation == "Log to Both" )
            {
                cout << "Configuration File Data" << endl;
                cout << "Monitor = " << monitor << " ms/cycle" << endl;
                cout << "Processor = " << processor << " ms/cycle" << endl;
                cout << "Scanner = " << scanner << " ms/cycle" << endl;
                cout << "Hard Drive = " << hdd << " ms/cycle" << endl;
                cout << "Keyboard = " << keyboard << " ms/cycle" << endl;
                cout << "Memory = " << memory << " ms/cycle" << endl;
                cout << "Projector = " << projector << " ms/cycle" << endl;
                getline( readIn, strInput, ':' );
                readIn >> logPath;
                cout << "Logged to: monitor and " << logPath << endl << endl;
                logExists = true;
            }
            else
            {
                cout << "No log file destination." << endl << endl;
            }
        }
        else{
            cout << "Could not open config file." << endl;
        }
        readIn.close();
        ofstream log;
        log.open( logPath.c_str() );
        if( logExists )
        {

            log << "Configuration File Data" << endl;
            log << "Monitor = " << monitor << " ms/cycle" << endl;
            log << "Processor = " << processor << " ms/cycle" << endl;
            log << "Scanner = " << scanner << " ms/cycle" << endl;
            log << "Hard Drive = " << hdd << " ms/cycle" << endl;
            log << "Keyboard = " << keyboard << " ms/cycle" << endl;
            log << "Memory = " << memory << " ms/cycle" << endl;
            log << "Projector = " << projector << " ms/cycle" << endl;
            if( logLocation == "Log to File" )
            {
                log << "Logged to: " << logPath << endl << endl;
            }
            if( logLocation == "Log to Both" )
            {
                log << "Logged to: monitor and " << logPath << endl << endl;
            }

        }

        config.m_version = version;
        config.m_path = path;
        config.m_monitor = monitor;
        config.m_processor = processor;
        config.m_scanner = scanner;
        config.m_hdd = hdd;
        config.m_keyboard = keyboard;
        config.m_memory = memory;
        config.m_projector = projector;
        config.m_logPath = logPath;
        config.m_logLocation = logLocation;


        MetaData( config.m_path, config, log );
        log.close();
        return config;
    }
//