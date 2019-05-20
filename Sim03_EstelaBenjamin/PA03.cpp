// Program Information ////
/**
  * @file PA03.cpp
  *
  * @brief Driver program to exercise the Config class
  *
  * @details Allows for testing all Config methods
  *             in an interactive operation
  *
  * @verion 1.00
  *		Benjamin Estela (9 February 2019)
  *		Initial development
  *
  * @version 1.01
  *     Benjamin Estela (13 March 2019)
  *     Update for new meta data and assignment 2
  *
  * @version 1.02
  *     Benjamin Estela (5 April 2019)
  *     Update for new meta data and assignment 3
  *
  * @note Requires Config.h, Config.cpp, MetaData.h, MetaData.cpp, pcb.h, pcb. cpp
  */
// Program Description/Support ////
/*
    This program uses various input/output files (ex. config_1.conf and
    Test_1.mdf) to read in specific meta data and output them alongside
    a proper configuration.
*/
// Precompiler Directives ////
//
/////   NONE
//
// Header Files ////
//
    #include <iostream>
    #include <fstream>
    #include <time.h>
    #include <chrono>
    #include <pthread.h>
    #include <semaphore.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <ctime>
    #include "Config.cpp"
    #include "MetaData.cpp"
    #include "pcb.cpp"
    using namespace std;
//
// Global Constant Definitions ////
//
/////   NONE
//
// Class Definitions ////
//
/////   NONE
//
// Free Function Prototypes ////
//
    void logConfig(Config config, std::ofstream& log);
//
// Main Function Implementation ////
//
    int main( int argc, char** argv )
    { //make; ./sim3 config_1.conf
        chrono::high_resolution_clock::time_point T1;
        T1 = chrono::high_resolution_clock::now();
        try{
            if( !argv[1] )
            {
                throw "No config file found.";
            }
        } catch( const char* MSG )
        {
            cout << MSG << endl;
        }
        Config config;
        Pcb pcb;
        pcb.setId( 0 );
        config = config.readConfig( argv[1], config );

        ofstream log;
        log.open( config.getLogPath().c_str() );
        //logConfig( config, log );

        ifstream metaFile;
        metaFile.open( config.getPath().c_str() );

        //srand(time(NULL));
        MetaData( config, pcb, metaFile, log, T1 );
        metaFile.close();
        log.close();
        return 0;
    }
//
// Free Function Implementation ////
//
/**
  * @brief Function reads the config file
  *
  * @details Taking in information from the config class, each variable
  *     is appropriately output
  *
  * @exception Boundary
  *     if no config, an error is shown
  *
  * @param[in] config is the class that holds the configuration values
  *
  * @param[in] log is the file to where the user can optionally log
  *             values to
  *
  * @param[out] values to log may be input
  *
  * @return None
  *
  * @note: requires and uses iostream and fstream tools
  *
  * @note: currently unused as of assignment 2
  */
    void logConfig( Config config, std::ofstream& log ){
        if( config.getLogLocation() == "Log to Monitor" || config.getLogLocation() == "Log to Both")
        {
            cout << "Configuration File Data" << endl;
            cout << "Version = " << config.getVersion() << endl;
            cout << "Meta Data File = " << config.getPath() << endl;
            cout << "Monitor = " << config.getMonitor() << " ms/cycle" << endl;
            cout << "Processor = " << config.getProcessor() << " ms/cycle" << endl;
            cout << "Scanner = " << config.getScanner() << " ms/cycle" << endl;
            cout << "Hard Drive = " << config.getHDD() << " ms/cycle" << endl;
            cout << "Keyboard = " << config.getKeyboard() << " ms/cycle" << endl;
            cout << "Memory = " << config.getMemory() << " ms/cycle" << endl;
            cout << "Projector = " << config.getProjector() << " ms/cycle" << endl;
            cout << "System Memory = " << config.getSysMemory() << " "
                 << config.getMemType() << endl;
            cout << "Memory Block Size = " << config.getBlockMemory() << " "
                 << config.getBlockType() << endl;
            cout << "Projector Quantity = " << config.getProjectorCount() << endl;
            cout << "Hard Drive Quantity = " << config.getHDDCount() << endl;

        }
        if( config.getLogLocation() == "Log to File" || config.getLogLocation() == "Log to Both")
        {
            log << "Configuration File Data" << endl;
            log << "Version = " << config.getVersion() << endl;
            log << "Meta Data File = " << config.getPath() << endl;
            log << "Monitor = " << config.getMonitor() << " ms/cycle" << endl;
            log << "Processor = " << config.getProcessor() << " ms/cycle" << endl;
            log << "Scanner = " << config.getScanner() << " ms/cycle" << endl;
            log << "Hard Drive = " << config.getHDD() << " ms/cycle" << endl;
            log << "Keyboard = " << config.getKeyboard() << " ms/cycle" << endl;
            log << "Memory = " << config.getMemory() << " ms/cycle" << endl;
            log << "Projector = " << config.getProjector() << " ms/cycle" << endl;
            log << "System Memory = " << config.getSysMemory() << " "
                << config.getMemType() << endl;
            log << "Memory Block Size = " << config.getBlockMemory() << " "
                 << config.getBlockType() << endl;
            log << "Projector Quantity = " << config.getProjectorCount() << endl;
            log << "Hard Drive Quantity = " << config.getHDDCount() << endl;

        }
        if( config.getLogLocation() == "Log to Monitor")
        {
            cout << "Logged to: monitor" << endl << endl;
        }
        if( config.getLogLocation() == "Log to File")
        {
            cout << "Logged to: " << config.getLogPath() << endl << endl;
            log << "Logged to: " << config.getLogPath() << endl << endl;
        }
        if( config.getLogLocation() == "Log to Both" ){
            cout << "Logged to: monitor and " << config.getLogPath() << endl << endl;
            log << "Logged to: monitor and " << config.getLogPath() << endl << endl;
        }
        if( config.getLogLocation() != "Log to Monitor" &&
            config.getLogLocation() != "Log to File" &&
            config.getLogLocation() != "Log to Both")
        {
            cout << "No log location provided." << endl;
        }

    }
//
//  Class/Data Structure Member Implementation ////
//
/////   NONE
//
//  Terminating Precompiler Directives ////
//
/////   NONE
//