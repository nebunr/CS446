// Class Implementation File Information ////
/**
  * @file pcb.cpp
  *
  * @brief Implementation file for pcb class
  *
  * @details Implements all multiline member methods of the pcb class
  *
  * @verion 1.00
  *		Benjamin Estela (13 March 2019)
  *		Initial development
  *
  * @note Requires pcb.h, pcbstates.h
  */
//
// Header Files ////
//
    #include <iostream>
    #include <fstream>
    #include "pcb.h"
    #include "pcbstates.h"

    using namespace std;
//

//
// Class/Data Structure Member Implementation ////
//
/**
  * @brief pcb default class constructor
  *
  */
    Pcb::Pcb()
    {
        int m_processstate = 0;
        int m_id = 0;
    }
    void Pcb::setProcessState( int processState )
    {
        if (processState == START ||
            processState == READY ||
            processState == RUNNING ||
            processState == WAITING ||
            processState == EXIT) {
            m_processState = processState;
        } else {
            cout << "Invalid process state set." << endl;
        }
    }
    void Pcb::setId(int id)
    {
            m_id = id;
    }
//