#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#pragma warning(disable : 4996)

static char nazwy[256][32];
int ind = 0;
// TODO: Zmienic na jakas liste 
struct FuncInfo
{
	char* nazwa;
	int linia;
	char* plik;
} typedef info;

static info def[256];
static defInd = 0;
static info proto[256];
static protoInd = 0;
static info call[256];
static callInd = 0;

void dodajNazwe(char* nazwa)
{
	for (int i = 0; i < ind; i++)
	{
		if (strcmp(nazwy[i], nazwa) == 0)
			return;
	}

	strcpy(nazwy[ind++], nazwa);
}

store_add_def(char* nazwa, int linia, char* plik)
{
	if (defInd > 255)
	{
		fprintf(stderr, "Przekroczono pojemnosc zbiornika na definicje funkcji!");
		return;
	}

	def[defInd].nazwa = malloc(sizeof(char) * strlen(nazwa));	// Kopiowanie nazwy funkcji
	if (def[defInd].nazwa != NULL)
		strcpy(def[defInd].nazwa, nazwa);

	def[defInd].linia = linia;

	def[defInd].plik = malloc(sizeof(char) * strlen(plik));		// Kopiowanie nazwy pliku
	if (def[defInd].plik != NULL)
		strcpy(def[defInd].plik, plik);

	defInd++;

	dodajNazwe(nazwa);
}

store_add_proto(char* nazwa, int linia, char* plik)
{
	if (protoInd > 255)
	{
		fprintf(stderr, "Przekroczono pojemnosc zbiornika na protoinicje funkcji!");
		return;
	}

	proto[protoInd].nazwa = malloc(sizeof(char) * strlen(nazwa));	// Kopiowanie nazwy funkcji
	if (proto[protoInd].nazwa != NULL)
		strcpy(proto[protoInd].nazwa, nazwa);

	proto[protoInd].linia = linia;

	proto[protoInd].plik = malloc(sizeof(char) * strlen(plik));		// Kopiowanie nazwy pliku
	if (proto[protoInd].plik != NULL)
		strcpy(proto[protoInd].plik, plik);

	protoInd++;

	dodajNazwe(nazwa);
}

store_add_call(char* nazwa, int linia, char* plik)
{
	if (callInd > 255)
	{
		fprintf(stderr, "Przekroczono pojemnosc zbiornika na callinicje funkcji!");
		return;
	}

	call[callInd].nazwa = malloc(sizeof(char) * strlen(nazwa));	// Kopiowanie nazwy funkcji
	if (call[callInd].nazwa != NULL)
		strcpy(call[callInd].nazwa, nazwa);

	call[callInd].linia = linia;

	call[callInd].plik = malloc(sizeof(char) * strlen(plik));		// Kopiowanie nazwy pliku
	if (call[callInd].plik != NULL)
		strcpy(call[callInd].plik, plik);

	callInd++;

	dodajNazwe(nazwa);
}





int main(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		analizatorSkladni(argv[i]);
	}

	/*printf("----Definicje\n");
	for (int i = 0; i < defInd; i++)
		printf("%s\n%d\n%s\n\n", def[i].nazwa, def[i].linia, def[i].plik);

	printf("----Prototypy\n");
	for (int i = 0; i < protoInd; i++)
		printf("%s\n%d\n%s\n\n", proto[i].nazwa, proto[i].linia, proto[i].plik);

	printf("----Wywolania\n");
	for (int i = 0; i < callInd; i++)
		printf("%s\n%d\n%s\n\n", call[i].nazwa, call[i].linia, call[i].plik);*/


	for (int j = 0; j < ind; j++)
	{
		printf("\n%s\n", nazwy[j]);
		printf("Definicje: \n");
		for (int i = 0; i < defInd; i++)
		{
			if (strcmp(def[i].nazwa, nazwy[j]) == 0)
				printf("\tplik: %s linia: %d\n", def[i].plik, def[i].linia);
		}
		printf("Prototypy: \n");
		for (int i = 0; i < protoInd; i++)
		{
			if (strcmp(proto[i].nazwa, nazwy[j]) == 0)
				printf("\tplik: %s linia: %d\n", proto[i].plik, proto[i].linia);
		}
		printf("Wywolania: \n");
		for (int i = 0; i < callInd; i++)
		{
			if (strcmp(call[i].nazwa, nazwy[j]) == 0)
				printf("\tplik: %s linia: %d\n", call[i].plik, call[i].linia);
		}
	}

	getch();

	return 0;
}