/**
 *  @file pessoa.c
 *  @brief Implementation of some function prototypes for project of aed1.
 *
 *  This file contains the implementations for
 *  some functions to process structs pessoa that will be needed for the aed1 project.
 *
 *  @author José Torres (jtorres@ufp.edu.pt)
 *  @bug No known bugs.
 */

#include "pessoa.h"

extern pessoa * personsDB;
extern int personDBSize;


/**
 *  Simple test client for the functions to manipulate pessoas
 */
void clientReadFilePerson() {
    pessoa * pessoasArray = NULL;
    int i, n = 0;
    // should use relative path instead: "../data/3persons.txt"
    pessoasArray = readFilePerson("/Users/ZeeCunha/Desktop/AED1/data/3persons.txt", &n);
    for (i=0; i<n; i++) {
        printPerson(&pessoasArray[i]);
    }

    readFilePersonFamily("/Users/ZeeCunha/Desktop/AED1/data/3persons-family.txt");
}

/**
   Simple test client 2 for the functions to manipulate pessoas
   Updates the database of persons (global variable personsDB)
 */
void clientReadFilePerson2() {
    pessoa  * pessoasArray = NULL;
    int i, n=0;

    // should use relative path instead: "../data/3persons.txt"
    pessoasArray = readFilePerson("/Users/ZeeCunha/Desktop/AED1/data/3persons.txt", &n);
    printf("\nArray lido do ficheiro 1:\n");
    for (i=0; i<n; i++) {
        printPerson(&pessoasArray[i]);
    }

    if (personDBSize == 0) {
        personsDB = pessoasArray;
        personDBSize = n;
    } else {
        personsDB = concatPersonArrays(personsDB, personDBSize, pessoasArray, n, 1);
        personDBSize = personDBSize + n;
    }

    pessoasArray = readFilePerson("/Users/ZeeCunha/Desktop/AED1/data/4persons.txt", &n);
    printf("\nArray lido do ficheiro 2:\n");
    for (i=0; i<n; i++) {
        printPerson(&pessoasArray[i]);
    }

    if (personDBSize == 0) {
        personsDB = pessoasArray;
        personDBSize = n;
    } else {
        personsDB = concatPersonArrays(personsDB, personDBSize, pessoasArray, n, 1);
        personDBSize = personDBSize + n;
    }

    // add a new person
    pessoa p = {"333333351","Ana Silva","20150101","Avenida dos Aliados Norte, 352","4249020","Paranhos"};
    personsDB = addPerson2PersonArray(personsDB, personDBSize, &p);
    personDBSize = personDBSize + 1;

    printf("\nConteudo da base de dados:\n");
    for (i=0; i<personDBSize; i++) {
        printPerson(&personsDB[i]);
    }

}

/**
 *  Prints information about one person in console
 *
 *  @param person person to print
 */
void printPerson(pessoa * person) {
    printf("\n\tNIF: %s\n\tNome: %s\n\tData de nascimento: %s\n\tCodigo Postal: %s\n\tFreguesia: %s\n",person->nif,person->nome,person->datanascimento,person->cod_postal,person->freguesia);
}

/**
 *  Read file with person's data and stores it in array
 *
 *  @param filename name of the file with data to load
 *  @param n        number of pessoa records that were read
 *
 *  @return pointer to pessoa array created
 */
pessoa * readFilePerson(char * filename, int * n){
    FILE * fp;
    pessoa * personsArray;
    char line[LINEMAXSIZE]; ///< esta variável será usada para guardar um parágrafo lido dum ficheiro de texto de pessoas
    int i = 0;
    fp = fopen(filename, "r");
    if (fp != NULL) {
        fscanf(fp,"%d\n", n);
        personsArray = newPersonArray((*n));
        while (!feof(fp) && i < (*n)) {
            fgets(line, LINEMAXSIZE, fp);
            parseLine2Person(line, &personsArray[i]);
            i++;
        }
        fclose(fp);
    } else return 0; // error readind file
    return personsArray;
}

/**
 *  Parses one line/paragraph from the ;-separated text file
 *  and fills the fields of variable person of type struct pessoa
 *
 *  @param line   (input) null terminated string with information about a person
 *  @param person (output) struct of type pessoa filled with info about the person
 */
void parseLine2Person(char * line, pessoa * person) {
    char * field_separator = ";\n"; // ";" and "\n" are the field separators
    char * field_person;
    field_person = strtok(line, field_separator);
    strcpy(person->nif,field_person);
    field_person = strtok(NULL, field_separator);
    strcpy(person->nome,field_person);
    field_person = strtok(NULL, field_separator);
    strcpy(person->datanascimento,field_person);
    field_person = strtok(NULL, field_separator);
    strcpy(person->morada,field_person);
    field_person = strtok(NULL, field_separator);
    strcpy(person->cod_postal,field_person);
    field_person = strtok(NULL, field_separator);
    strcpy(person->freguesia,field_person);
}

/**
 *  Read file with person's family data, TO DO: change function prototype!
 *
 *  @param filename name of the file
 *
 *  @return number of persons read or error code (-1)
 */
int readFilePersonFamily(char * filename){
    FILE * fp;
    char line[LINEMAXSIZE];
    int i = 0, n;
    fp = fopen(filename, "r");
    if (fp != NULL) {
        fscanf(fp,"%d\n", &n);
        while (!feof(fp) && i < n) {
            fgets(line, LINEMAXSIZE, fp);
            processLine2PersonFamily(line);
            i++;
        }
        fclose(fp);
    } else return -1; // error reading file
    return n;
}

/**
 *  Parses line from person family text file
 *
 *  @param line (input) null terminated string with information about a person's relatives
 */
void processLine2PersonFamily(char * line){
    char * field_separator = ";\n"; // ";" and "\n" are the field separators
    char * field_person;
    char nif1[10], nif2[10];
    int num_relatives, i=0;
    field_person = strtok(line, field_separator);
    strcpy(nif1,field_person);
    printf("\nNIF da pessoa: %s.",nif1);
    field_person = strtok(NULL, field_separator);
    num_relatives = atoi(field_person);
    printf(" Numero de familiares: %d. Lista dos seus NIFs: ",num_relatives);
    while (i < num_relatives) {
        field_person = strtok(NULL, field_separator);
        strcpy(nif2,field_person);
        printf("%s; ",nif2);
        i++;
    }
}


/**
 *  Concatenate / joins two pessoa arrays. Second array can be static or dynamic allocated.
 *
 *  @param personsArrayBase         personsArrayBase description
 *  @param personsArrayBaseSize     personsArrayBaseSize description
 *  @param personsArray2            personsArray2 description
 *  @param personsArray2Size        personsArray2Size description
 *  @param isArray2DynamicAllocated boolean value isArray2DynamicAllocated can be 1 (true) or 0 (false)
 *
 *  @return <#return value description#>
 */
pessoa * concatPersonArrays(pessoa * personsArrayBase, int personsArrayBaseSize, pessoa * personsArray2, int personsArray2Size, int isArray2DynamicAllocated){
    personsArrayBase = realloc(personsArrayBase, (personsArrayBaseSize + personsArray2Size) * sizeof(pessoa));
    memcpy(&personsArrayBase[personsArrayBaseSize], personsArray2, personsArray2Size * sizeof(pessoa));
    if (isArray2DynamicAllocated != 0) {
        freePersonArray(personsArray2);
    }
    return personsArrayBase;
}

/**
 *  Add just one person to the array. The person (argument person) must be statically declared
 *
 *  @param personsArrayBase     personsArrayBase description
 *  @param personsArrayBaseSize personsArrayBaseSize description
 *  @param person               person to be added to the end of the array
 *
 *  @return <#return value description#>
 */
pessoa * addPerson2PersonArray(pessoa * personsArrayBase, int personsArrayBaseSize, pessoa * person){
    return concatPersonArrays(personsArrayBase, personsArrayBaseSize, person, 1, 0);
}

/**
 *  Creates a new dynamic array of persons with size N
 *
 *  @param N size of array to be dynamically created
 *
 *  @return pointer to new array person created
 */
pessoa * newPersonArray(int N){
    return (pessoa *) malloc(sizeof(pessoa) * N);
}

/**
 *  Frees the dynamic array p from the memory (deletes the array)
 *
 *  @param p p description
 */
void freePersonArray(pessoa * p){
    free(p);
}




