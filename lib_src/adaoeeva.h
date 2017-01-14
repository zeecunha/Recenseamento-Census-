/**
 *  @file adaoeeva.h
 *  @brief implementação de todas as funções do Programa.
 *
 *
 *  @author José Cunha (28018@ufp.edu.pt)
 *
 */


#ifndef ADAOEEVA_H_INCLUDED
#define ADAOEEVA_H_INCLUDED

#include "stringsorting.h"


void listar(pessoa* personsDB, int personDBSize);
void criarpessoa();
void MSD_menu(pessoa * pessoas, int n);//menu MSD
void MSD_nif(pessoa* pessoas, int N);
void MSD_nome(pessoa* pessoas, int N);
void MSD_data(pessoa* pessoas,int N);
void MSD_codpostal(pessoa* pessoas,int N);
void MSD_freguesia(pessoa* pessoas,int N);
void LSD_menu(pessoa * pessoas, int n);//menu LSD
void LSD_nif(pessoa* pessoas, int N);
void LSD_nome(pessoa* pessoas, int N);
void LSD_data(pessoa* pessoas,int N);
void LSD_codpostal(pessoa* pessoas,int N);
void LSD_freguesia(pessoa* pessoas,int N);
void guarda_txt(pessoa * personsDB,int personDBSize);
void atualizardados();
void menu();



#endif // ADAOEEVA_H_INCLUDED
