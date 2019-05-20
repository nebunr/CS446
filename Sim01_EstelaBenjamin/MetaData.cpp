// Implementation File Information ////
/**
  * @file MetaData.cpp
  *
  * @brief Implementation file for Meta Data Free Functions
  *
  * @details Implements all functions found in Meta Data
  *
  * @verion 1.00
  *		Benjamin Estela (18 February 2019)
  *		Initial development
  *
  * @note Requires Config.h, MetaData.h
  */
//
// Header Files ////
//
    #include <iostream>
    #include <fstream>
    #include "Config.h"
    #include "MetaData.h"
    using namespace std;
//
// Free Function Implementation ////
//
/**
  * @brief Function begins reading in meta data file for output
  *
  * @details Taking in information from the config class, the meta
  *     can be opened for output to the terminal and/or log file
  *
  * @exception Boundary
  *     if meta data file cannot be read, an error is shown
  *
  * @exception Boundary
  *     if improper cycle, an error is shown
  *
  * @param[in] file holds the file path to where the meta data is opened
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
  * @note: requires and uses iostream and fstream tools. Calls
  *         PrintMeta within function
  */
    void MetaData( std::string file, Config config, std::ofstream& log )
    {
        char temp;
        char code;
        string descriptor;
        int cycle;
        string strInput;
        ifstream readIn;
        readIn.open( file.c_str() );
        if( readIn.is_open() )
        {
            getline( readIn, strInput ); //read: Start
            cout << "Meta-Data Metrics" << endl;
            if( config.getLogLocation() == "Log to Monitor"
               || config.getLogLocation() == "Log to Both" )
            {
                log << "Meta-Data Metrics" << endl;
            }
            while( readIn )
            {
                readIn.get( code );
                getline( readIn, strInput, '{' );
                getline( readIn, descriptor, '}' );
                readIn >> cycle;
                getline( readIn, strInput, ';');
                readIn.get( temp );
                if(cycle > 0)
                {
                    PrintMeta( config, code, descriptor, cycle, log );
                }
                else if( cycle != 0 )
                {
                    cout << "Incorrect or negative non-zero "
                         << "number of cycles found." << endl;
                }

            }
        }
        else
        {
            cout << "Could not open meta data file." << endl;
        }
        readIn.close();
    }
/**
  * @brief Function outputs meta data
  *
  * @details Using variables defined in the MetaData function, the meta data
  *             is properly output onto either the terminal and/or log file
  *
  * @exception Boundary
  *     if improper code or descriptor, a warning message is given
  *
  *
  * @param[in] config is the class that holds the configuration values
  *
  * @param[in] code is the char that holds the meta data code
  *
  * @param[in] descriptor is the string that holds the meta data descriptor
  *
  * @param[in] cycle is the int that holds the number of cycles
  *
  * @param[in] log is the file to where the user can optionally log
  *             values to
  *
  * @param[out] values to log may be input
  *
  * @return None
  *
  * @note: requires and uses iostream and fstream tools
  */
    void PrintMeta( Config config,
                    char code,
                    std::string descriptor,
                    int cycle,
                    std::ofstream& log )
    {
        int logDir = config.intLocation();
        switch( code )
        {
            case 'S':
                if( descriptor == "begin" )
                {
                    cout << endl;
                }
                else if( descriptor == "finish" )
                {
                    cout << endl;
                }
                else
                {
                    cout << endl;
                }
                break;
            case 'A':
                if( descriptor == "begin" )
                {
                    cout << endl;
                }
                else if( descriptor == "finish" )
                {
                    cout << endl;
                }
                else
                {
                    cout << endl;
                }
                break;
            case 'P':
                if( descriptor == "run" )
                {
                    switch( logDir )
                    {
                        case 0:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getProcessor() * cycle
                                 << " ms" << endl;
                            break;
                        case 1:
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getProcessor() * cycle
                                << " ms" << endl;
                            break;
                        case 2:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getProcessor() * cycle
                                 << " ms" << endl;
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getProcessor() * cycle
                                << " ms" << endl;
                            break;
                        default:
                            break;
                    }

                }
                else
                {
                    cout << "Missing or incorrect meta data descriptor."
                         << endl;
                }
                break;
            case 'I':
                if( descriptor == "hard drive" )
                {
                    switch( logDir )
                    {
                        case 0:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getHDD() * cycle
                                 << " ms" << endl;
                            break;
                        case 1:
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getHDD() * cycle
                                << " ms" << endl;
                            break;
                        case 2:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getHDD() * cycle
                                 << " ms" << endl;
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getHDD() * cycle
                                << " ms" << endl;
                            break;
                        default:
                            break;
                    }
                }
                else if( descriptor == "keyboard" )
                {
                    switch( logDir )
                    {
                        case 0:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getKeyboard() * cycle
                                 << " ms" << endl;
                            break;
                        case 1:
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getKeyboard() * cycle
                                << " ms" << endl;
                            break;
                        case 2:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getKeyboard() * cycle
                                 << " ms" << endl;
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getKeyboard() * cycle
                                << " ms" << endl;
                            break;
                        default:
                            break;
                    }
                }
                else if( descriptor == "scanner" )
                {
                    switch( logDir )
                    {
                        case 0:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getScanner() * cycle
                                 << " ms" << endl;
                            break;
                        case 1:
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getScanner() * cycle
                                << " ms" << endl;
                            break;
                        case 2:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getScanner() * cycle
                                 << " ms" << endl;
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getScanner() * cycle
                                << " ms" << endl;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    cout << "Missing or incorrect meta data descriptor."
                         << endl;
                }
                break;
            case 'O':
                if( descriptor == "hard drive" )
                {
                    switch( logDir )
                    {
                        case 0:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getHDD() * cycle
                                 << " ms" << endl;
                            break;
                        case 1:
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getHDD() * cycle
                                << " ms" << endl;
                            break;
                        case 2:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getHDD() * cycle
                                 << " ms" << endl;
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getHDD() * cycle
                                << " ms" << endl;
                            break;
                        default:
                            break;
                    }
                }
                else if( descriptor == "monitor" )
                {
                    switch( logDir )
                    {
                        case 0:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getMonitor() * cycle
                                 << " ms" << endl;
                            break;
                        case 1:
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getMonitor() * cycle
                                << " ms" << endl;
                            break;
                        case 2:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getMonitor() * cycle
                                 << " ms" << endl;
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getMonitor() * cycle
                                << " ms" << endl;
                            break;
                        default:
                            break;
                    }
                }
                else if( descriptor == "projector" )
                {
                    switch( logDir )
                    {
                        case 0:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getProjector() * cycle
                                 << " ms" << endl;
                            break;
                        case 1:
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getProjector() * cycle
                                << " ms" << endl;
                            break;
                        case 2:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getProjector() * cycle
                                 << " ms" << endl;
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getProjector() * cycle
                                << " ms" << endl;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    cout << "Missing or incorrect meta data descriptor."
                         << endl;
                }
                break;
            case 'M':
                if( descriptor == "block" )
                {
                    switch( logDir )
                    {
                        case 0:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getMemory() * cycle
                                 << " ms" << endl;
                            break;
                        case 1:
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getMemory() * cycle
                                << " ms" << endl;
                            break;
                        case 2:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getMemory() * cycle
                                 << " ms" << endl;
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getMemory() * cycle
                                << " ms" << endl;
                            break;
                        default:
                            break;
                    }
                }
                else if( descriptor == "allocate" )
                {
                    switch( logDir )
                    {
                        case 0:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getMemory() * cycle
                                 << " ms" << endl;
                            break;
                        case 1:
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getMemory() * cycle
                                << " ms" << endl;
                            break;
                        case 2:
                            cout << code << "{" << descriptor << "}" << cycle
                                 << " - " << config.getMemory() * cycle
                                 << " ms" << endl;
                            log << code << "{" << descriptor << "}" << cycle
                                << " - " << config.getMemory() * cycle
                                << " ms" << endl;
                            break;
                        default:
                            break;
                    }
                }
                else
                {
                    cout << "Missing or incorrect meta data descriptor."
                         << endl;
                }
                break;
            default:
                if( code != '.' )
                {
                    cout << "Error finding meta date code." << endl;
                }
                break;
        }
    }
//