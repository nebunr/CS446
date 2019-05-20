// Program Information ////
/**
  * @file PA01.cpp
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
  * @note Requires Config.h, Config.cpp, MetaData.h, MetaData.cpp
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
    #include "Config.cpp"
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
/////   NONE
//
// Main Function Implementation ////
//
    int main( int argc, char** argv )
    {
        try{
            if( !argv[1] )
            {
                throw "No config file found.";
            }
            //cout << "Config File: " << argv[1] << "\n";
        } catch( const char* MSG )
        {
            cout << MSG << endl;
        }
        Config config;
        config = config.readConfig( argv[1], config );
        //MetaData( config.getPath(), config );
        return 0;
    }
//
// Free Function Implementation ////
//
/////   NONE
//
//  Class/Data Structure Member Implementation ////
//
/////   NONE
//
//  Terminating Precompiler Directives ////
//
/////   NONE
//