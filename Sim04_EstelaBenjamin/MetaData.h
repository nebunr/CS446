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
  * @version 1.02
  *     Benjamin Estela (5 April 2019)
  *     Update for new meta data and assignment 3
  *
  * @version 1.03
  *     Benjamin Estela (23 April 2019)
  *     Update for new meta data and assignment 4
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
struct MD
{
    char m_code;
    string m_descriptor;
    int m_cycle;
};
struct Counts
{
    int projCount = 0;
    int hddCount = 0;
    int sysBlock = 0;
};
//
// Free Function Prototypes ////
//
    void ReadMeta( std::ofstream& log,
                   std::ifstream& metaFile,
                   Config config,
                   Pcb &pcb,
                   chrono::high_resolution_clock::time_point T1 );
    void PrintMeta( std::ofstream& log,
                    std::ifstream& metaFile,
                    Config config,
                    Pcb &pcb,
                    chrono::high_resolution_clock::time_point T1,
                    pthread_t tid,
                    Counts &sysCount,
                    MD md );
    void SortPS( std::ofstream& log,
                  std::ifstream& metaFile,
                  Config config,
                  Pcb &pcb,
                  chrono::high_resolution_clock::time_point T1,
                  pthread_t tid,
                  Counts &sysCount,
                  MD md[],
                  int max );
    int MaxIO( int count[], int max );
    void SortSJF( std::ofstream& log,
                  std::ifstream& metaFile,
                  Config config,
                  Pcb &pcb,
                  chrono::high_resolution_clock::time_point T1,
                  pthread_t tid,
                  Counts &sysCount,
                  MD md[],
                  int max );
    int MinJob( int count[], int max );
    double TimeStamp( chrono::high_resolution_clock::time_point T1 );
    void *ThreadMeta( void* time );
    void WaitTime( int time );
    int assignMemory( Config config, Counts &sysCount );
    int checkCount ( int max, int count );
//
// Terminating Precompiler Directives ////
//
    #endif //METADATA_H
//