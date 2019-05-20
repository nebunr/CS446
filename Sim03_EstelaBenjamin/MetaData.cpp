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
  *	@version 1.01
  *     Benjamin Estela (13 March 2019)
  *     Update for new meta data and assignment 2
  *
  * @version 1.02
  *     Benjamin Estela (5 April 2019)
  *     Update for new meta data and assignment 3
  *
  * @note Requires Config.h, MetaData.h, pcbstates.h
  */
//
// Header Files ////
//
    #include "Config.h"
    #include "MetaData.h"
    #include "pcbstates.h"
    //#include "pcb.h"
    using namespace std;
    using namespace std::chrono;

//
// Global Constant Definitions ////
//
    pthread_mutex_t mutex;
    sem_t mutexArray[2];
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
  * @param[in] config is the class that holds the configuration values
  *
  * @param[in] pcb is the class that holds the process state and id
  *
  * @param[in] metaFile holds the file path to where the meta data is opened
  *
  * @param[in] log is the file to where the user can optionally log
  *             values to
  *
  * @param[in] T1 is the timer used for time stamping during output
  *
  * @param[out] values to log may be input
  *
  * @return None
  *
  * @note: requires and uses iostream and fstream tools. Calls
  *         PrintMeta within function
  */
    void MetaData( Config config,
                    Pcb &pcb,
                    std::ifstream& metaFile,
                    std::ofstream& log,
                    chrono::high_resolution_clock::time_point T1 )
    {
        char temp;
        char code;
        string descriptor;
        int cycle;
        string strInput;
        int count = 0;

        if( metaFile.is_open() )
        {
            Arg arg;
            struct Arg * argPtr = (struct Arg *)malloc(sizeof(struct Arg));
            argPtr->pa_T1 = T1;
            pthread_t tid;
            pthread_mutex_init( &mutex, nullptr );
            sem_init(&mutexArray[0], 0,
                    (unsigned int)(config.getHDDCount())); //for hdd
            sem_init(&mutexArray[1], 0,
                    (unsigned int)(config.getProjectorCount())); //for projector
            Counts sysCount;
            sysCount.sysBlock = config.getSysMemory() + 1;
            getline(metaFile, strInput); //read: Start
            while ( metaFile ) {
                argPtr->pcb_id = pcb.getId();
                metaFile.get( code );
                argPtr->meta_case = code;
                getline( metaFile, strInput, '{' );
                getline( metaFile, descriptor, '}' );
                argPtr->meta_descriptor = descriptor;
                metaFile >> cycle;
                getline( metaFile, strInput, ';' );
                metaFile.get( temp );
                if( cycle >= 0 )
                {
                    PrintMeta( config,
                               code,
                               descriptor,
                               cycle,
                               log,
                               T1,
                               pcb ,
                               count,
                               argPtr,
                               tid,
                               sysCount );
                }
                else
                {
                    cout << "Incorrect or negative "
                         << "number of cycles found." << endl;
                }
            }
            pthread_mutex_destroy( &mutex );
            int i;
            for(i = 0; i < 2; i++)
            {
                sem_destroy( &mutexArray[i] );
            }
        }
        else
        {
            cout << "Could not open Meta Data file." << endl;
        }
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
  * @param[in] T1 is the timer used for time stamping during output
  *
  * @param[in] pcb is the class that holds the process state and id
  *
  * @param[in] count is the int that sets m_id in pcb
  *
  * @param[in] argPtr is the struct pointer that holds in variables for the
  *     pthread_create function
  *
  * @param[in] tid id the pthread_t that holds the pthread used for threading
  *
  * @param[in] sysCount is a struct that holds counts for projector, hdd,
  *     and system memory
  *
  * @param[out] values to log may be input
  *
  * @return None
  *
  * @note: requires and uses iostream and fstream tools
  */
    void PrintMeta ( Config config,
                       char code,
                       std::string descriptor,
                       int cycle,
                       std::ofstream& log,
                       chrono::high_resolution_clock::time_point T1,
                       Pcb &pcb,
                       int &count,
                       Arg *argPtr,
                       pthread_t tid,
                       Counts &sysCount )
    {
        switch( code )
        {
            case 'S':
                if( descriptor == "begin" )
                {
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 )
                             << " - " << "Simulator program starting" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                    config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 )
                            <<  " - " << "Simulator program starting" << endl;
                    }
                }
                else if( descriptor == "finish" )
                {
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - "
                             << "Simulator program ending" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - "
                            << "Simulator program ending" << endl;
                    }
                }
                else
                {
                    cout << "Missing or incorrect meta data descriptor."
                         << endl;
                }
                break;
            case 'A':
                if( descriptor == "begin" )
                {
                    pcb.setId( ++count );
                    pcb.setProcessState( START );
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - OS: preparing process "
                             << pcb.getId() << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - OS: preparing process "
                            << pcb.getId() << endl;
                    }
                    pcb.setProcessState( READY );
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - OS: starting process "
                             << pcb.getId() << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - OS: starting process "
                            << pcb.getId() << endl;
                    }
                }
                else if( descriptor == "finish" )
                {
                    pcb.setProcessState( EXIT );
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - OS: removing process "
                             << pcb.getId() << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - OS: removing process "
                            << pcb.getId() << endl;
                    }
                }
                else
                {
                    cout << "Missing or incorrect meta data descriptor."
                         << endl;
                }
                break;
            case 'P':
                if( descriptor == "run" )
                {
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": start processing action" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": start processing action" << endl;
                    }
                    pcb.setProcessState( RUNNING );
                    WaitTime( config.getProcessor() * cycle);
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": end processing action" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": end processing action" << endl;
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
                    argPtr->config_cycle = config.getHDD() * cycle;
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": start hard drive input on HDD "
                            << sysCount.hddCount << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": start hard drive input on HDD "
                            << sysCount.hddCount << endl;
                    }
                    //pthread_mutex_lock( &mutex );
                    sem_wait( &mutexArray[0]) ;
                    pcb.setProcessState( WAITING );
                    pthread_create( &tid, nullptr, ThreadMeta, (void*)argPtr );
                    pthread_join( tid, nullptr );
                    pcb.setProcessState( READY );
                    sem_post( &mutexArray[0] );
                    //pthread_mutex_unlock( &mutex );
                    sysCount.hddCount = checkCount(config.getHDDCount(),
                            ++sysCount.hddCount);
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": end hard drive input" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                        << ": end hard drive input" << endl;
                    }

                }
                else if( descriptor == "keyboard" )
                {
                    argPtr->config_cycle = config.getKeyboard() * cycle;
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": start keyboard input" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                        << ": start keyboard input" << endl;
                    }
                    pthread_mutex_lock( &mutex );
                    pcb.setProcessState( WAITING );
                    pthread_create( &tid, nullptr, ThreadMeta, (void*)argPtr );
                    pthread_join( tid, nullptr );
                    pcb.setProcessState( READY );
                    pthread_mutex_unlock( &mutex );
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": end keyboard input" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": end keyboard input" << endl;
                    }
                }
                else if( descriptor == "scanner" )
                {
                    argPtr->config_cycle = config.getScanner() * cycle;
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": start scanner input" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": start scanner input" << endl;
                    }
                    pthread_mutex_lock( &mutex );
                    pcb.setProcessState( WAITING );
                    pthread_create( &tid, nullptr, ThreadMeta, (void*)argPtr );
                    pthread_join( tid, nullptr );
                    pcb.setProcessState( READY );
                    pthread_mutex_unlock( &mutex );
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": end scanner input" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": end scanner input" << endl;
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
                    argPtr->config_cycle = config.getHDD() * cycle;
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": start hard drive output on HDD "
                             << sysCount.hddCount << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": start hard drive output on HDD "
                            << sysCount.hddCount << endl;
                    }
                    //pthread_mutex_lock( &mutex );
                    sem_wait( &mutexArray[0] );
                    pcb.setProcessState( WAITING );
                    pthread_create( &tid, nullptr, ThreadMeta, (void*)argPtr );
                    pthread_join( tid, nullptr );
                    pcb.setProcessState( READY );
                    //pthread_mutex_unlock( &mutex );
                    sem_post( &mutexArray[0] );
                    sysCount.hddCount = checkCount(config.getHDDCount(),
                            ++sysCount.hddCount);
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": end hard drive output" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": end hard drive output" << endl;
                    }

                }
                else if( descriptor == "monitor" )
                {
                    argPtr->config_cycle = config.getMonitor() * cycle;
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": start monitor output" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": start monitor output" << endl;
                    }
                    pthread_mutex_lock( &mutex );
                    pcb.setProcessState( WAITING );
                    pthread_create( &tid, nullptr, ThreadMeta, (void*)argPtr );
                    pthread_join( tid, nullptr );
                    pcb.setProcessState( READY );
                    pthread_mutex_unlock( &mutex );
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": end monitor output" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": end monitor output" << endl;
                    }
                }
                else if( descriptor == "projector" )
                {
                    argPtr->config_cycle = config.getProjector() * cycle;
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": start projector output on PROJ "
                             << sysCount.projCount << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": start projector output on PROJ "
                            << sysCount.projCount << endl;
                    }
                    //pthread_mutex_lock( &mutex );
                    sem_wait( &mutexArray[1] );
                    pcb.setProcessState( WAITING );
                    pthread_create( &tid, nullptr, ThreadMeta, (void*)argPtr );
                    pthread_join( tid, nullptr );
                    pcb.setProcessState( READY );
                    //pthread_mutex_unlock( &mutex );
                    sem_post( &mutexArray[1] );
                    sysCount.projCount = checkCount( config.getProjectorCount(),
                            ++sysCount.projCount );
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": end projector output" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": end projector output" << endl;
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
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": start memory blocking" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                        << ": start memory blocking" << endl;
                    }
                    WaitTime( config.getMemory() * cycle );
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": end memory blocking" << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": end memory blocking" << endl;
                    }

                }
                else if( descriptor == "allocate" )
                {
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": allocating memory" << endl;
                    }

                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": allocating memory" << endl;
                    }
                    WaitTime( config.getMemory() * cycle );
                    int tempMem = assignMemory( config, sysCount );
                    if( config.getLogLocation() == "Log to Monitor" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        cout << TimeStamp( T1 ) << " - Process " << pcb.getId()
                             << ": memory allocated at 0x" << hex
                             << tempMem << endl;
                    }
                    if( config.getLogLocation() == "Log to File" ||
                        config.getLogLocation() == "Log to Both" )
                    {
                        log << TimeStamp( T1 ) << " - Process " << pcb.getId()
                            << ": memory allocated at 0x" << hex
                            << tempMem << endl;
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
                    cout << "Error finding meta data code." << endl;
                }
                break;
        }
    }
/**
  * @brief ThreadMeta calls WaitTime to wait for a set amount of time
  *
  * @details Depending on the log location, a different int value is returned,
  *         this is so a switch statement can be used in PrintMeta
  *
  * @param[in] pArg is the void that is set to the struct pointer for Arg that
  *     holds in config_cycle
  *
  * @return integer 0
  *
  * @note None
  */
    void *ThreadMeta( void *pArg )
    {
        struct Arg *data = ( struct Arg* )pArg;


        WaitTime( data->config_cycle );

        return nullptr;
    }
/**
  * @brief TimeStamp return a double to print the time since the process
  *     started
  *
  * @param[in] T1 is the timer used for time stamping during output
  *
  * @return double of elapsed time
  *
  * @note None
  */
    double TimeStamp( chrono::high_resolution_clock::time_point T1 )
    {
        return duration_cast<duration<double>>( high_resolution_clock::now() - T1 ).count();
    }
/**
  * @brief WaitTime waits a set amount of microseconds
  *
  * @param[in] time is in integer to determine the time for usleep to occur
  *
  * @return None
  *
  * @note None
  */
    void WaitTime( int time )
    {
        auto temp = ( unsigned int )time;
        usleep( temp * 1000 );
    }
/**
  * @brief assignMemory properly generates a system memory value for PrintMeta
  *
  * @param[in] config is the class that holds the configuration values
  *
  * @param[in] sysCount is a struct that holds the current memory value
  *
  * @return an integer tied to a struct holding the new memory value
  *
  * @note None
  */
    int assignMemory( Config config, Counts &sysCount )
    {
        int multiplier = 0;
        if( config.getMemType() == "kbytes" )
        {
            multiplier = 1;
        }
        else if( config.getMemType() == "Mbytes" )
        {
            multiplier = 1000;
        }
        else if( config.getMemType() == "Gbytes" )
        {
            multiplier = 1000000;
        }
        else
        {
            cout << "Incorrect System Memory type (kbytes, Mbytes, Gbytes)."
                 << endl;
            return 0;
        }
        if ( config.getSysMemory() <= sysCount.sysBlock )
        {
            sysCount.sysBlock = 0;
            return sysCount.sysBlock;
        }
        sysCount.sysBlock += config.getBlockMemory() * multiplier;
        return sysCount.sysBlock;

    }
/**
 * @brief checkCount checks if max is less than or equal to count
 *      and resets count if needed
 *
 * @param[in] max is an integer max value used for comparison
 *
 * @param[in] count is an integer compared to max
 *
 * @return count is in integer that is return
 *
 * @note None
 */
    int checkCount ( int max, int count )
    {
        if ( max <= count )
        {
            count = 0;
        }
        return count;
    }
//