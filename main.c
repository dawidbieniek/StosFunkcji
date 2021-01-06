#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#pragma warning(disable : 4996)


char** nazwy;				// lista nazw funkcji
int ileNazw = 0;			// liczba nazw w liscie

struct FuncInfo
{
	char* nazwa;
	int linia;
	char* plik;
} typedef funcInfo;

static funcInfo def[256];
static int ileDef = 0;
static funcInfo proto[256];
static int ileProto = 0;
static funcInfo call[256];
static int ileCall = 0;

void dodajNazwe(char* nazwa)
{
	if (nazwy == NULL)								// rezerwuje pamiec, gdy lista jest pusta
	{
		nazwy = malloc(sizeof(char*));
		if (nazwy == NULL)							// nie udalo sie zarezerwowac pamieci -> error
		{
			fprintf(stderr, "Nie mozna stworzyc listy nazw!!!");
			return;
		}
	}
	else
	{
		for (int i = 0; i < ileNazw; i++)			// jezeli nazwa juz wystepuje w liscie, wyjdz z funkcji
		{
			if (strcmp(nazwy[i], nazwa) == 0)
				return;
		}

		char** tmp = realloc(nazwy, sizeof(char*) * (ileNazw + 1));	
		if (tmp != NULL)
			nazwy = tmp;
		else										// nie udalo sie zarezerwowac pamieci -> error
		{
			fprintf(stderr, "Nie mozna dodac nazwy do listy!!!");
			return;
		}
	}

	nazwy[ileNazw] = malloc(sizeof(char) * strlen(nazwa));	// dodawanie nazwy do listy
	if (nazwy[ileNazw] != NULL)
		strcpy(nazwy[ileNazw++], nazwa);
}

void store_add_def(char* nazwa, int linia, char* plik)
{
	if (ileDef > 255)
	{
		fprintf(stderr, "Przekroczono pojemnosc zbiornika na definicje funkcji!");
		return;
	}

	def[ileDef].nazwa = malloc(sizeof(char) * strlen(nazwa));	// Kopiowanie nazwy funkcji
	if (def[ileDef].nazwa != NULL)
		strcpy(def[ileDef].nazwa, nazwa);

	def[ileDef].linia = linia;

	def[ileDef].plik = malloc(sizeof(char) * strlen(plik));		// Kopiowanie nazwy pliku
	if (def[ileDef].plik != NULL)
		strcpy(def[ileDef].plik, plik);

	ileDef++;

	dodajNazwe(nazwa);
}

void store_add_proto(char* nazwa, int linia, char* plik)
{
	if (ileProto > 255)
	{
		fprintf(stderr, "Przekroczono pojemnosc zbiornika na protoinicje funkcji!");
		return;
	}

	proto[ileProto].nazwa = malloc(sizeof(char) * strlen(nazwa));	// Kopiowanie nazwy funkcji
	if (proto[ileProto].nazwa != NULL)
		strcpy(proto[ileProto].nazwa, nazwa);

	proto[ileProto].linia = linia;

	proto[ileProto].plik = malloc(sizeof(char) * strlen(plik));		// Kopiowanie nazwy pliku
	if (proto[ileProto].plik != NULL)
		strcpy(proto[ileProto].plik, plik);

	ileProto++;

	dodajNazwe(nazwa);
}

void store_add_call(char* nazwa, int linia, char* plik)
{
	if (ileCall > 255)
	{
		fprintf(stderr, "Przekroczono pojemnosc zbiornika na callinicje funkcji!");
		return;
	}

	call[ileCall].nazwa = malloc(sizeof(char) * strlen(nazwa));	// Kopiowanie nazwy funkcji
	if (call[ileCall].nazwa != NULL)
		strcpy(call[ileCall].nazwa, nazwa);

	call[ileCall].linia = linia;

	call[ileCall].plik = malloc(sizeof(char) * strlen(plik));		// Kopiowanie nazwy pliku
	if (call[ileCall].plik != NULL)
		strcpy(call[ileCall].plik, plik);

	ileCall++;

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


	for (int j = 0; j < ileNazw; j++)
	{
		printf("\n%s\n", nazwy[j]);
		printf("Definicje: \n");
		for (int i = 0; i < ileDef; i++)
		{
			if (strcmp(def[i].nazwa, nazwy[j]) == 0)
				printf("\tplik: %s linia: %d\n", def[i].plik, def[i].linia);
		}
		printf("Prototypy: \n");
		for (int i = 0; i < ileProto; i++)
		{
			if (strcmp(proto[i].nazwa, nazwy[j]) == 0)
				printf("\tplik: %s linia: %d\n", proto[i].plik, proto[i].linia);
		}
		printf("Wywolania: \n");
		for (int i = 0; i < ileCall; i++)
		{
			if (strcmp(call[i].nazwa, nazwy[j]) == 0)
				printf("\tplik: %s linia: %d\n", call[i].plik, call[i].linia);
		}
	}

	getch();

	return 0;
}