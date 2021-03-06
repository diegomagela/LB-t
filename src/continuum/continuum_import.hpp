#ifndef CONTINUUM_IMPORT_HPP_INCLUDED
#define CONTINUUM_IMPORT_HPP_INCLUDED

/**
 * \file     continuum_import.hpp
 * \mainpage Class members for importing macroscopic values
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>

#include "../general/paths.hpp"


/**\fn         Import
 * \brief      Import macroscopic values from *.bin-file
 *
 * \param[in]  name   the import file name holding the macroscopic quantities
 * \param[in]  step   the current time step that will be used for the name
*/
template <unsigned int NX, unsigned int NY, unsigned int NZ, typename T>
void Continuum<NX,NY,NZ,T>::Import(std::string const name, unsigned int const step)
{
    std::string const fileName = OUTPUT_BIN_PATH + std::string("/") + name + std::string("_") + std::to_string(step) + std::string(".bin");

    if(fopen(fileName.c_str(), "rb+") != nullptr)
    {
        FILE * const importFile = fopen(fileName.c_str(), "rb+");
        fread(M_, 1, MEM_SIZE_, importFile);
        fclose(importFile);
    }
    else
    {
        std::cerr << "Fatal error: Could not import macroscopic values from disk." << std::endl;
        exit(EXIT_FAILURE);
    }
}

#endif // CONTINUUM_IMPORT_HPP_INCLUDED
