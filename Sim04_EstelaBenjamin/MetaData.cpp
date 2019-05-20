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
  * @version 1.03
  *     Benjamin Estela (23 April 2019)
  *     Update for new meta data and assignment 4
  *
  * @note Requires Config.h, MetaData.h, pcbstates.h
  */
//
// Header Files ////
//
    #include "Config.h"
    #include "MetaData.h"
    #include "pcbstates.h"
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
    void ReadMeta( std::ofstream& log,
                   std::ifstream& metaFile,
                   Config config,
                   Pcb &pcb,
                   chrono::high_resolution_clock::time_point T1 )
    {
        MD md[50];
        pthread_t tid;
        pthread_mutex_init( &mutex, nullptr );
        sem_init(&mutexArray[0], 0,
                 (unsigned int)(config.getHDDCount())); //for hdd
        sem_init(&mutexArray[1], 0,
                 (unsigned int)(config.getProjectorCount())); //for projector
        Counts sysCount;
        sysCount.sysBlock = config.getSysMemory() + 1;
        int count = 0;
        int index = 0;
        string strInput;
        char temp;
        if ( metaFile.is_open() )
        {
            getline(metaFile, strInput); //read: Start
            while ( metaFile )
            {
                metaFile.get( md[index].m_code );
                getline( metaFile, strInput, '{' );
                getline( metaFile, md[index].m_descriptor, '}' );
                metaFile >> md[index].m_cycle;
                getline( metaFile, strInput, ';' );
                metaFile.get( temp );
                index++;
            }
            if ( config.getSchedule() == "FIFO")
            {
                for( int i = 0; i < index; i++ )
                {
                    if( md[i].m_cycle >= 0 )
                    {
                        if ( md[i].m_code == 'A' &&
                             md[i].m_descriptor == "begin" )
                        {
                            pcb.setId( ++count );
                        }
                        PrintMeta(log,
                                  metaFile,
                                  config,
                                  pcb,
                                  T1,
                                  tid,
                                  sysCount,
                                  md[i] );
                    }
                    else
                    {
                        cout << "Incorrect or negative "
                             << "number of cycles found." << endl;
                    }
                }
            }
            else if ( config.getSchedule() == "PS")
            {
                SortPS(log,
                       metaFile,
                       config,
                       pcb,
                       T1,
                       tid,
                       sysCount,
                       md,
                       index );
            }
            else if ( config.getSchedule() == "SJF")
            {
                SortSJF(log,
                        metaFile,
                        config,
                        pcb,
                        T1,
                        tid,
                        sysCount,
                        md,
                        index );
            }
            else
            {
                cout << "Invalid CPU Scheduling Code" << endl;
            }
            pthread_mutex_destroy( &mutex );
            sem_destroy( &mutexArray[0] );
            sem_destroy( &mutexArray[1] );
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
    void PrintMeta( std::ofstream& log,
                       std::ifstream& metaFile,
                       Config config,
                       Pcb &pcb,
                       chrono::high_resolution_clock::time_point T1,
                       pthread_t tid,
                       Counts &sysCount,
                       MD md )
    {
        switch( md.m_code )
        {
            case 'S':
                if( md.m_descriptor == "begin" )
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
                else if( md.m_descriptor == "finish" )
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
                if( md.m_descriptor == "begin" )
                {
                    //pcb.setId( ++count );
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
                else if( md.m_descriptor == "finish" )
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
                if( md.m_descriptor == "run" )
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
                    WaitTime( config.getProcessor() * md.m_cycle );
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
                if( md.m_descriptor == "hard drive" )
                {

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
                    sem_wait( &mutexArray[0]) ;
                    pcb.setProcessState( WAITING );
                    int temp = config.getHDD() * md.m_cycle;
                    pthread_create( &tid, nullptr, ThreadMeta, &temp );
                    pthread_join( tid, nullptr );
                    pcb.setProcessState( READY );
                    sem_post( &mutexArray[0] );
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
                else if( md.m_descriptor == "keyboard" )
                {
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
                    int temp = config.getKeyboard() * md.m_cycle;
                    pthread_create( &tid, nullptr, ThreadMeta, &temp );
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
                else if( md.m_descriptor == "scanner" )
                {
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
                    int temp = config.getScanner() * md.m_cycle;
                    pthread_create( &tid, nullptr, ThreadMeta, &temp );
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
                if( md.m_descriptor == "hard drive" )
                {
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
                    sem_wait( &mutexArray[0] );
                    pcb.setProcessState( WAITING );
                    int temp = config.getHDD() * md.m_cycle;
                    pthread_create( &tid, nullptr, ThreadMeta, &temp );
                    pthread_join( tid, nullptr );
                    pcb.setProcessState( READY );
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
                else if( md.m_descriptor == "monitor" )
                {
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
                    int temp = config.getMonitor() * md.m_cycle;
                    pthread_create( &tid, nullptr, ThreadMeta, &temp );
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
                else if( md.m_descriptor == "projector" )
                {
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
                    sem_wait( &mutexArray[1] );
                    pcb.setProcessState( WAITING );
                    int temp = config.getProjector() * md.m_cycle;
                    pthread_create( &tid, nullptr, ThreadMeta, &temp );
                    pthread_join( tid, nullptr );
                    pcb.setProcessState( READY );
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
                if( md.m_descriptor == "block" )
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
                    WaitTime( config.getMemory() * md.m_cycle );
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
                else if( md.m_descriptor == "allocate" )
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
                    WaitTime( config.getMemory() * md.m_cycle );
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
                if( md.m_code != '.' )
                {
                    cout << "Error finding meta data code." << endl;
                }
                break;
        }
    }
/**
  * @brief Function prepares the meta data for output in priority scheduling
  *
  * @param[in] log is the file to where the user can optionally log
  *             values to
  *
  * @param[in] config is the class that holds the configuration values
  *
  * @param[in] pcb is the class that holds the process state and id
  *
  * @param[in] T1 is the timer used for time stamping during output
  *
  * @param[in] tid id the pthread_t that holds the pthread used for threading
  *
  * @param[in] sysCount is a struct that holds counts for projector, hdd,
  *     and system memory
  *
  * @param[in] md is the struct that holds all of the meta data
  *
  * @param[in] max is an integer that holds the amount of tasks
  *
  * @param[out] values to log may be input
  *
  * @return None
  *
  * @note: requires and uses iostream tools
  */
    void SortPS( std::ofstream& log,
                 std::ifstream& metaFile,
                 Config config,
                 Pcb &pcb,
                 chrono::high_resolution_clock::time_point T1,
                 pthread_t tid,
                 Counts &sysCount,
                 MD md[],
                 int max )
    {
        int i = 0;
        int count[20];
        int countIndex = 0;
        for( int x = 0; x <= 20; x++ )
        {
            count[x] = 0;
        }
        if( md[0].m_code == 'S' )
        {
            PrintMeta(log,
                      metaFile,
                      config,
                      pcb,
                      T1,
                      tid,
                      sysCount,
                      md[i] );
            i++;
        }
        for( ; i < max; )
        {
            while( md[i].m_descriptor != "finish" )
            {
                if ( md[i].m_code == 'I' || md[i].m_code == 'O' )
                {
                    count[countIndex]++;
                }
                i++;
            }
            countIndex++;
            i++;
        }
        countIndex--;
        int temp[countIndex];
        for( int x = 0; x < countIndex; x++ )
        {
            count[x]++;
            temp[x] = count[x];
        }
        int array[countIndex];
        int finish;
        for( int x = 0; x < countIndex; x++ )
        {
            array[x] = MaxIO(temp, countIndex);
        }
        for( int x = 0; x < countIndex; x++ )
        {
            finish = 0;
            for( i = 1; i < max - 1; i++ )
            {
                if ( finish == array[x] )
                {
                    pcb.setId(array[x] + 1);
                    PrintMeta(log,
                              metaFile,
                              config,
                              pcb,
                              T1,
                              tid,
                              sysCount,
                              md[i] );
                }
                if ( md[i].m_code == 'A' && md[i].m_descriptor == "finish" )
                {
                    finish++;
                }
            }
        }
        PrintMeta(log,
                  metaFile,
                  config,
                  pcb,
                  T1,
                  tid,
                  sysCount,
                  md[max-1] );
    }
/**
  * @brief MaxJob returns an integer of the index of the largest
  *         value in an array
  *
  * @param[in] count[] is an integer array holding the job counts
  *
  * @param[in] max is an integer holding the amount of processes
  *
  * @return integer of the index of the largest value
  *
  * @note None
  */
    int MaxIO(int count[], int max)
    {
        int maxIndex = 0;
        int maxValue = count[0];
        for( int i = 0; i < max; i++ )
        {
            if( count[i] > maxValue )
            {
                maxIndex = i;
                maxValue = count[maxIndex];
            }
        }
        count[maxIndex] = -1;
        return maxIndex;
    }
/**
  * @brief Function prepares the meta data for output with shortest job first
  *
  * @param[in] log is the file to where the user can optionally log
  *             values to
  *
  * @param[in] config is the class that holds the configuration values
  *
  * @param[in] pcb is the class that holds the process state and id
  *
  * @param[in] T1 is the timer used for time stamping during output
  *
  * @param[in] tid id the pthread_t that holds the pthread used for threading
  *
  * @param[in] sysCount is a struct that holds counts for projector, hdd,
  *     and system memory
  *
  * @param[in] md is the struct that holds all of the meta data
  *
  * @param[in] max is an integer that holds the amount of tasks
  *
  * @param[out] values to log may be input
  *
  * @return None
  *
  * @note: requires and uses iostream tools
  */
    void SortSJF( std::ofstream& log,
                  std::ifstream& metaFile,
                  Config config,
                  Pcb &pcb,
                  chrono::high_resolution_clock::time_point T1,
                  pthread_t tid,
                  Counts &sysCount,
                  MD md[],
                  int max )
    {
        int i = 0;
        int count[20];
        int countIndex = 0;
        for( int x = 0; x <= 20; x++ )
        {
            count[x] = 0;
        }
        if( md[0].m_code == 'S' )
        {
            PrintMeta(log,
                      metaFile,
                      config,
                      pcb,
                      T1,
                      tid,
                      sysCount,
                      md[i] );
            i++;
        }
        for( ; i < max; )
        {
            while( md[i].m_descriptor != "finish" )
            {
                count[countIndex]++;
                i++;
            }
            countIndex++;
            i++;
        }
        countIndex--;
        int temp[countIndex];
        for( int x = 0; x < countIndex; x++ )
        {
            count[x]++;
            temp[x] = count[x];
        }
        int array[countIndex];
        int finish;
        for( int x = 0; x < countIndex; x++ )
        {
            array[x] = MinJob(temp, countIndex);
        }
        for( int x = 0; x < countIndex; x++ )
        {
            finish = 0;
            for( i = 1; i < max - 1; i++ )
            {
                if ( finish == array[x] )
                {
                    pcb.setId(array[x] + 1);
                    PrintMeta(log,
                              metaFile,
                              config,
                              pcb,
                              T1,
                              tid,
                              sysCount,
                              md[i] );
                }
                if ( md[i].m_code == 'A' && md[i].m_descriptor == "finish" )
                {
                    finish++;
                }
            }
        }
        PrintMeta(log,
                  metaFile,
                  config,
                  pcb,
                  T1,
                  tid,
                  sysCount,
                  md[max-1] );
    }
/**
  * @brief MinJob returns an integer of the index of the smallest
  *         value in an array
  *
  * @param[in] count[] is an integer array holding the job counts
  *
  * @param[in] max is an integer holding the amount of processes
  *
  * @return integer of the index of the smallest value
  *
  * @note None
  */
    int MinJob(int count[], int max)
    {
        int minIndex = 0;
        int minValue = count[0];
        for( int i = 0; i < max; i++ )
        {
            if( count[i] < minValue )
            {
                minIndex = i;
                minValue = count[minIndex];
            }
        }
        count[minIndex] = 999;
        return minIndex;
    }
/**
  * @brief TimeStamp returns a double to print the time since the process
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
  * @brief ThreadMeta calls WaitTime to wait for a set amount of time
  *
  * @details Depending on the log location, a different int value is returned,
  *         this is so a switch statement can be used in PrintMeta
  *
  * @param[in] cycle is in integer which holds the cycle time
  *
  * @return integer 0
  *
  * @note None
  */
    void *ThreadMeta( void* time )
    {
        int wait = *((int*) time);
        WaitTime( wait );
        return nullptr;
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
        auto wait = ( unsigned int )time;
        usleep( wait * 1000 );
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