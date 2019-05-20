// Class Header File Information ////
/**
  * @file Config.h
  *
  * @brief Definition file for Config class
  *
  * @details Specifies all member methods of the Config Class
  *
  * @verion 1.00
  *		Benjamin Estela (9 February 2019)
  *		Initial development
  *
  *	@version 1.01
  *		Benjamin Estela (13 March 2019)
  *		Inclusion of m_memType and m_sysMemory
  *
  * @version 1.02
  *		Benjamin Estela (31 March 2019)
  *		Inclusion of block memory and projector and hdd count
  *
  * @version 1.03
  *     Benjamin Estela (22 April 2019)
  *     Inclusion of quantum and schedule
  *
  * @note None
  */
//
// Precompiler Directives ////
//
    #ifndef CONFIG_H
    #define CONFIG_H
//
// Class Definitions ////
//
    class Config
    {
        public:
            // Constructor
            Config();

            // Get Methods
            float getVersion()              {return m_version;}
            std::string getPath()           {return m_path;}
            int getQuantum()                {return m_quantum;}
            std::string getSchedule()       {return m_schedule;}
            int getProcessor()              {return m_processor;}
            int getMonitor()                {return m_monitor;}
            int getHDD()                    {return m_hdd;}
            int getProjector()              {return m_projector;}
            int getKeyboard()               {return m_keyboard;}
            int getMemory()                 {return m_memory;}
            int getScanner()                {return m_scanner;}
            std::string getMemType()        {return m_memType;}
            int getSysMemory()              {return m_sysMemory;}
            std::string getBlockType()      {return m_blockType;}
            int getBlockMemory()            {return m_blockMemory;}
            int getProjectorCount()         {return m_projectorCount;}
            int getHDDCount()               {return m_hddCount;}
            std::string getLogPath()        {return m_logPath;}
            std::string getLogLocation()    {return m_logLocation;}

            // Multiline member functions
            Config readConfig( const char* FILE, Config config );

        private:
            float m_version;
            std::string m_path;
            int m_quantum;
            std::string m_schedule;
            int m_processor;
            int m_monitor;
            int m_hdd;
            int m_projector;
            int m_keyboard;
            int m_memory;
            int m_scanner;
            std::string m_memType;
            int m_sysMemory;
            std::string m_blockType;
            int m_blockMemory;
            int m_projectorCount;
            int m_hddCount;
            std::string m_logLocation;
            std::string m_logPath;
    };
//
// Terminating Precompiler Directives ////
//
    #endif //CONFIG_H
//