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
            int getMonitor()                {return m_monitor;}
            int getProcessor()              {return m_processor;}
            int getScanner()                {return m_scanner;}
            int getHDD()                    {return m_hdd;}
            int getKeyboard()               {return m_keyboard;}
            int getMemory()                 {return m_memory;}
            int getProjector()              {return m_projector;}
            std::string getMemType()        {return m_memType;}
            int getSysMemory()              {return m_sysMemory;}
            std::string getBlockType()        {return m_blockType;}
            int getBlockMemory()              {return m_blockMemory;}
            int getProjectorCount()         {return m_projectorCount;}
            int getHDDCount()               {return m_hddCount;}
            std::string getLogPath()        {return m_logPath;}
            std::string getLogLocation()    {return m_logLocation;}

            // Multiline member functions
            Config readConfig( const char* FILE, Config config );

        private:
            float m_version;
            std::string m_path;
            int m_monitor;
            int m_processor;
            int m_scanner;
            int m_hdd;
            int m_keyboard;
            int m_memory;
            int m_projector;
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