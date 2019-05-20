// Class Header File Information ////
/**
  * @file pcbstates.h
  *
  * @brief Definition file for pcbstates
  *
  * @details Specifies values for m_processstate in the pcb class
  *
  * @verion 1.00
  *		Benjamin Estela (13 March 2019)
  *		Initial development
  *
  * @note None
  */
#ifndef PCBSTATES_H
#define PCBSTATES_H

enum {
    START,
    READY,
    RUNNING,
    WAITING,
    EXIT,
};

#endif //PCBSTATES_H
