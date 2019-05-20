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
  * @note None
  */
//
// Precompiler Directives ////
//
    #ifndef METADATA_H
    #define METADATA_H
//
// Free Function Prototypes ////
//
    void MetaData( std::string file, Config config, std::ofstream& log );
    void PrintMeta( Config config,
                    char code,
                    std::string descriptor,
                    int cycle,
                    std::ofstream& log );
//
// Terminating Precompiler Directives ////
//
    #endif //METADATA_H
//