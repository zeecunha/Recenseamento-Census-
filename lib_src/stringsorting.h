
// *** END ***
#ifndef STRINGSORTING_H_INCLUDED
#define STRINGSORTING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "pessoa.h"

// tamanho do alfabeto de chars com 8 bits (ASCII)
#define ALFABETO 256

// tamanho do alfabeto de numeros inteiros {0,1,2,...,8,9}
#define INT_RADIX 10

typedef struct {
    char** str;  // array of strings
    int* len;  // array of string lengths
    int* keys;  // key arrays de um alfabeto com STR_KEY_RADIX simbolos
    int N; // number of strings (size of array of strings)
} StringKeyElementsArray;

typedef struct {
    char** str;  // array of strings
    int* len;  // array of string lengths
    int N; // number of strings (size of array of strings)
} StringElementsArray;

void createStringElementsArray(StringElementsArray* si, int N);
void freeStringElementsArray(StringElementsArray* si);

void createStringElementsArrayAndFillNif(StringElementsArray* a, int N, pessoa* person);
void createStringElementsArrayAndFillNome(StringElementsArray* a, int N, pessoa* person);
void createStringElementsArrayAndFillData(StringElementsArray* a, int N, pessoa* person);
void createStringElementsArrayAndFillCodpostal(StringElementsArray * a, int N, pessoa * pessoas);
void createStringElementsArrayAndFillFreguesia(StringElementsArray * a, int N, pessoa * pessoas);

void lsd_sort(StringElementsArray* a, int N, int W, int R);
void msd_sort_whithout_cutoff(StringElementsArray* a, StringElementsArray* aux, int lo, int hi, int d, int R);

#endif // STRINGSORTING_H_INCLUDED
