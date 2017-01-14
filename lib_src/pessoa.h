/**
 *  @file pessoa.h
 *  @brief Some function prototypes for project of aed1.
 *
 *  This file contains the declaration for
 *  some functions to process structs pessoa that will be needed for the aed1 project.
 *
 *  @author José Torres (jtorres@ufp.edu.pt)
 *  @bug No known bugs.
 */

#ifndef PESSOA_LIB_h
#define PESSOA_LIB_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define LINEMAXSIZE 300

/**
   @brief Struct describing the several fields about each person
 
 Detailed description for struct pessoa. All fields are of type string.
 
 */
typedef struct {
    char nif[10]; ///< null-terminated 9-digit portuguese Tax identification numbers (TIN). Example “333333333\0”
    char nome[100]; ///< null-terminated person’s name. Example “Cristiano Pedro Silva”
    char datanascimento[9]; ///< null-terminated 8-digit birth date (yyyymmdd). Example “20000624” for 24th of june 2000.
    char morada[100]; ///< null-terminated address: street and door number. Example “Praça 9 de Abril, 349” (UFP main address)
    char cod_postal[8]; ///< null-terminated 7-digit postal code. Example “4249004” for 4249-004 (UFP postal code)
    char freguesia[100]; ///< null-terminated district name. Example “Paranhos\0” (UFP district)
} pessoa;

void clientReadFilePerson();
void clientReadFilePerson2();

void printPerson(pessoa * person);

pessoa * readFilePerson(char * filename, int * n);
void parseLine2Person(char * line, pessoa * person);

int readFilePersonFamily(char * filename);
void processLine2PersonFamily(char * line);

pessoa * concatPersonArrays(pessoa * personsArrayBase, int personsArrayBaseSize, pessoa * personsArray2, int personsArray2Size, int isArray2DynamicAllocated);
pessoa * addPerson2PersonArray(pessoa * personsArrayBase, int personsArrayBaseSize, pessoa * person);
pessoa * newPersonArray(int N);
void freePersonArray(pessoa * p);

#endif

