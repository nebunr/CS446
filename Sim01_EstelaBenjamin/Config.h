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
                Config();   // Constructor
                //~Config();

                // Get Methods
                // getVersion is currently unused
                float getVersion()              {return m_version;}
                std::string getPath()           {return m_path;}
                int getMonitor()                {return m_monitor;}
                int getProcessor()              {return m_processor;}
                int getScanner()                {return m_scanner;}
                int getHDD()                    {return m_hdd;}
                int getKeyboard()               {return m_keyboard;}
                int getMemory()                 {return m_memory;}
                int getProjector()              {return m_projector;}
                std::string getLogPath()        {return m_logPath;}
                std::string getLogLocation()    {return m_logLocation;}

                //Multiline member functions
                int intLocation();
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
                std::string m_logPath;
                std::string m_logLocation;
    };
//
// Terminating Precompiler Directives ////
//
    #endif //CONFIG_H
//