///
///  @file main.c
///  @brief main for AED1 project1
///
///  Created by José Manuel Torres on 28/09/15.
///  Copyright (c) 2015 ___JOSETORRES___. All rights reserved.
///

#include <stdio.h>
#include <string.h>
#include <time.h>
#include "pessoa.h"
#include "adaoeeva.h"

/**
 *  Persons database global variable
 */
pessoa* personsDB;
int personDBSize; ///< personDB size

int main(int argc, const char* argv[])
{
	int i = 0;
	personsDB = NULL;
	personDBSize = 0;
	personsDB = readFilePerson("/Users/ZeeCunha/Desktop/AED1/data/3persons.txt", &personDBSize);
	for (i = 0; i < personDBSize; i++)
	{
		printPerson(&personsDB[i]);
	}
    menu();

	return 0;
}


