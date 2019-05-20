// Class Header File Information ////
/**
  * @file pcb.h
  *
  * @brief Definition file for pcb class
  *
  * @details Specifies all member methods of the pbc class
  *
  * @verion 1.00
  *		Benjamin Estela (13 March 2019)
  *		Initial development
  *
  * @note None
  */
//
// Precompiler Directives ////
//
    #ifndef PCB_H
    #define PCB_H
//
// Class Definitions ////
//
    class Pcb
    {
        public:
            Pcb();
            //~Pcb();

            int getProcessState()   {return m_processState;}
            int getId()             {return m_id;}
            void setProcessState(int processState);
            void setId(int id);

        private:
            int m_processState;
            int m_id;
    };
//
// Terminating Precompiler Directives ////
//
    #endif //PCB_H
//