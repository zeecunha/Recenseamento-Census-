#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lib_util.h"
#include "stringsorting.h"


void createStringElementsArray(StringElementsArray * si, int N)
{
	si->N = N;
	si->str = (char **) malloc(sizeof(char *) * N);
	si->len = (int *) malloc(sizeof(int) * N);
	return;
}


void freeStringElementsArray(StringElementsArray * si)
{
	free(si->str);
	free(si->len);
	return;
}

///PARA NIF
void createStringElementsArrayAndFillNif(StringElementsArray * a, int N, pessoa * pessoas)
{
	int i;
	createStringElementsArray(a, N);
	for (i = 0; i < N; i++)
	{
		a->str[i] = pessoas[i].nif;
		a->len[i] = (int) strlen(pessoas[i].nif);
	}
	return;
}
///PARA NOME
void createStringElementsArrayAndFillNome(StringElementsArray * a, int N, pessoa * pessoas)
{
	int i;
	createStringElementsArray(a, N);
	for (i = 0; i < N; i++)
	{
		a->str[i] = pessoas[i].nome;
		a->len[i] = (int) strlen(pessoas[i].nome);
	}
	return;
}
///PARA DATA
void createStringElementsArrayAndFillData(StringElementsArray * a, int N, pessoa * pessoas)
{
	int i;
	createStringElementsArray(a, N);
	for (i = 0; i < N; i++)
	{
		a->str[i] = pessoas[i].datanascimento;
		a->len[i] = (int) strlen(pessoas[i].datanascimento);
	}
	return;
}
///PARA CODIGO POSTAL
void createStringElementsArrayAndFillCodpostal(StringElementsArray * a, int N, pessoa * pessoas)
{
	int i;
	createStringElementsArray(a, N);
	for (i = 0; i < N; i++)
	{
		a->str[i] = pessoas[i].cod_postal;
		a->len[i] = (int) strlen(pessoas[i].cod_postal);
	}
	return;
}
///PARA FREGUESIA
void createStringElementsArrayAndFillFreguesia(StringElementsArray * a, int N, pessoa * pessoas)
{
	int i;
	createStringElementsArray(a, N);
	for (i = 0; i < N; i++)
	{
		a->str[i] = pessoas[i].freguesia;
		a->len[i] = (int) strlen(pessoas[i].freguesia);
	}
	return;
}
/*************************************************************************
 * LSD Radix Sort
 ************************************************************************/

void lsd_sort(StringElementsArray * a, int N, int W, int R)
{
	int i, r, d, c;
	int * count = newIntArray(R + 1);
	StringElementsArray aux; // aux Array
	createStringElementsArray(&aux, N); // create aux array

	for (d = W - 1; d >= 0; d--)
	{
		// reset count[] array
		for (i = 0; i < R + 1; i++)
			count[i] = 0;
		// compute frequency counts
		for (i = 0; i < N; i++)
			count[a->str[i][d] + 1]++;
		// transform counts to indicies
		for (r = 0; r < R; r++)
			count[r + 1] += count[r];
		// distribute
		for (i = 0; i < N; i++)
		{
			c = a->str[i][d];
			aux.str[count[c]] = a->str[i];
			aux.len[count[c]] = a->len[i];
			count[c]++;
		}
		// copy back
		for (i = 0; i < N; i++)
		{
			a->str[i] = aux.str[i];
			a->len[i] = aux.len[i];
		}
	}
	freeStringElementsArray(&aux);
}

/*************************************************************************
 * MSD Radix Sort (without cutoff)
 ************************************************************************/

void msd_sort_whithout_cutoff(StringElementsArray *a, StringElementsArray *aux, int lo, int hi, int d, int R)
{
	int i, r, c;
	int * count = newIntArray(R + 2);
	// reset count[] array
	for (i = 0; i < R + 2; i++)
		count[i] = 0;

	if (hi <= lo)
		return;

	// compute frequency counts
	for (i = lo; i <= hi; i++)
	{
		c = (d < a->len[i]) ? (a->str[i][d]) : -1;
		count[c + 2]++;
	}

	// transform counts to indicies
	for (r = 0; r < R + 1; r++)
		count[r + 1] += count[r];

	// distribute
	for (i = lo; i <= hi; i++)
	{
		c = (d < a->len[i]) ? (a->str[i][d]) : -1;
		aux->str[count[c + 1]] = a->str[i];
		aux->len[count[c + 1]] = a->len[i];
		count[c + 1]++;
	}

	// copy back
	for (i = lo; i <= hi; i++)
	{
		a->str[i] = aux->str[i - lo];
		a->len[i] = aux->len[i - lo];
	}

	// recursively sort for each character
	for (r = 0; r < R; r++)
		msd_sort_whithout_cutoff(a, aux, lo + count[r], lo + count[r + 1] - 1, d + 1, R);

	free(count);
}
