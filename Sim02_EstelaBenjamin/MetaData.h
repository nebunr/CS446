// Header File Information ////
/**
  * @file MetaData.h
  *
  * @brief Definition file for Meta Data Free Functions Prototypes
  *
  * @details Specifies all member methods of the Config Class
  *
  * @verion 1.00
  *		Benjamin Estela (18 February 2019)
  *		Initial development
  *
  *	@version 1.01
  *     Benjamin Estela (13 March 2019)
  *     Update for new meta data and assignment 2
  *
  * @note None
  */
//
// Precompiler Directives ////
//
    #ifndef METADATA_H
    #define METADATA_H
    //#include <chrono>
    #include "pcb.h"
//
// Data Structure Member Implementation ////
//
struct Arg{
    int pcb_id;
    int config_cycle = 0;
    char meta_case;
    string meta_descriptor;
    std::chrono::high_resolution_clock::time_point pa_T1;
};
//
// Free Function Prototypes ////
//
    void MetaData( Config config,
                   Pcb &pcb,
                   std::ifstream& metaFile,
                   std::ofstream& log,
                   chrono::high_resolution_clock::time_point T1 );
    void PrintMeta( Config config,
                       char code,
                       std::string descriptor,
                       int cycle,
                       std::ofstream& log,
                       chrono::high_resolution_clock::time_point T1,
                       Pcb &pcb,
                       int &count,
                       Arg *argPtr,
                       pthread_t tid);
    void *ThreadMeta( void *pArg);
    double TimeStamp( chrono::high_resolution_clock::time_point T1 );
    void WaitTime( int time );
    int assignMemory( Config config );
//
// Terminating Precompiler Directives ////
//
    #endif //METADATA_H
//