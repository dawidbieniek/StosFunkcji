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

static funcInfo* def;	// lista definicji funkcji
static int ileDef = 0;	// liczba elementow listy definicji funkcji
static funcInfo* proto;	// lista prototypow funkcji
static int ileProto = 0;// liczba elementow listy prototypow funkcji
static funcInfo* call;	// lista wywolan funkcji
static int ileCall = 0;	// liczba elementow listy wywolan funkcji
static funcInfo* use;	// lista uzyc funkcji
static int ileUse = 0;	// liczba elementow listy uzyc funkcji

static char* ostatniaNazwaDefinicji;

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
	if (def == NULL)								// rezerwuje pamiec, gdy lista jest pusta
	{
		def = malloc(sizeof(funcInfo));
		if (def == NULL)							// nie udalo sie zarezerwowac pamieci -> error
		{
			fprintf(stderr, "Nie mozna stworzyc listy definicji!!!");
			return;
		}
	}
	else
	{
		funcInfo* tmp = realloc(def, sizeof(funcInfo) * (ileDef + 1));
		if (tmp != NULL)
			def = tmp;
		else										// nie udalo sie zarezerwowac pamieci -> error
		{
			fprintf(stderr, "Nie mozna dodac definicji do listy!!!");
			return;
		}
	}

	def[ileDef].nazwa = malloc(sizeof(char) * strlen(nazwa));	// dodawanie nazwy do elementu
	if (def[ileDef].nazwa != NULL)
		strcpy(def[ileDef].nazwa, nazwa);

	def[ileDef].plik = malloc(sizeof(char) * strlen(plik));	// dodawanie nazwy pliku do elementu
	if (def[ileDef].plik != NULL)
		strcpy(def[ileDef].plik, plik);

	def[ileDef++].linia = linia;

	ostatniaNazwaDefinicji = malloc(sizeof(char) * strlen(nazwa));	// zapisywanie nazwy definicji
	if (ostatniaNazwaDefinicji != NULL)
		strcpy(ostatniaNazwaDefinicji, nazwa);

	dodajNazwe(nazwa);
}

void store_add_proto(char* nazwa, int linia, char* plik)
{
	if (proto == NULL)								// rezerwuje pamiec, gdy lista jest pusta
	{
		proto = malloc(sizeof(funcInfo));
		if (proto == NULL)							// nie udalo sie zarezerwowac pamieci -> error
		{
			fprintf(stderr, "Nie mozna stworzyc listy prototypow!!!");
			return;
		}
	}
	else
	{
		funcInfo* tmp = realloc(proto, sizeof(funcInfo) * (ileProto + 1));
		if (tmp != NULL)
			proto = tmp;
		else										// nie udalo sie zarezerwowac pamieci -> error
		{
			fprintf(stderr, "Nie mozna dodac prototypu do listy!!!");
			return;
		}
	}

	proto[ileProto].nazwa = malloc(sizeof(char) * strlen(nazwa));	// dodawanie nazwy do elementu
	if (proto[ileProto].nazwa != NULL)
		strcpy(proto[ileProto].nazwa, nazwa);

	proto[ileProto].plik = malloc(sizeof(char) * strlen(plik));	// dodawanie nazwy pliku do elementu
	if (proto[ileProto].plik != NULL)
		strcpy(proto[ileProto].plik, plik);

	proto[ileProto++].linia = linia;

	dodajNazwe(nazwa);
}

void store_add_call(char* nazwa, int linia, char* plik)
{
	if (call == NULL)								// rezerwuje pamiec, gdy lista jest pusta
	{
		call = malloc(sizeof(funcInfo));
		if (call == NULL)							// nie udalo sie zarezerwowac pamieci -> error
		{
			fprintf(stderr, "Nie mozna stworzyc listy wywolan!!!");
			return;
		}
	}
	else
	{
		funcInfo* tmp = realloc(call, sizeof(funcInfo) * (ileCall + 1));
		if (tmp != NULL)
			call = tmp;
		else										// nie udalo sie zarezerwowac pamieci -> error
		{
			fprintf(stderr, "Nie mozna dodac wywolania do listy!!!");
			return;
		}
	}

	call[ileCall].nazwa = malloc(sizeof(char) * strlen(nazwa));	// dodawanie nazwy do elementu
	if (call[ileCall].nazwa != NULL)
		strcpy(call[ileCall].nazwa, nazwa);

	call[ileCall].plik = malloc(sizeof(char) * strlen(plik));	// dodawanie nazwy pliku do elementu
	if (call[ileCall].plik != NULL)
		strcpy(call[ileCall].plik, plik);

	call[ileCall++].linia = linia;

	dodajNazwe(nazwa);
}

void store_add_use(char* nazwa)		// lista call wykorzystuje strukture funcInfo do przechowywania nazw (lepiej bylo by uzyc nowej struktury)
{
	if (use == NULL)								// rezerwuje pamiec, gdy lista jest pusta
	{
		use = malloc(sizeof(funcInfo));
		if (use == NULL)							// nie udalo sie zarezerwowac pamieci -> error
		{
			fprintf(stderr, "Nie mozna stworzyc listy uzyc!!!");
			return;
		}
	}
	else
	{
		for (int i = 0; i < ileUse; i++)			// jezeli nazwa usytej funkcji juz wystepuje w liscie, dodaj liczbe wystapien
		{
			if (strcmp(use[i].plik, nazwa) == 0)
			{
				use[i].linia++;
				return;
			}
		}

		funcInfo* tmp = realloc(use, sizeof(funcInfo) * (ileUse + 1));
		if (tmp != NULL)
			use = tmp;
		else										// nie udalo sie zarezerwowac pamieci -> error
		{
			fprintf(stderr, "Nie mozna dodac uzycia do listy!!!");
			return;
		}
	}

	use[ileUse].nazwa = malloc(sizeof(char) * strlen(ostatniaNazwaDefinicji));	// dodawanie nazwy do elementu
	if (use[ileUse].nazwa != NULL)
		strcpy(use[ileUse].nazwa, ostatniaNazwaDefinicji);

	use[ileUse].plik = malloc(sizeof(char) * strlen(nazwa));	// dodawanie nazwy pliku do elementu
	if (use[ileUse].plik != NULL)
		strcpy(use[ileUse].plik, nazwa);

	use[ileUse].linia = 1;

	ileUse++;
}


int main(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		analizatorSkladni(argv[i]);
	}

	for (int j = 0; j < ileNazw; j++)
	{
		int w = 0;

		printf("%s\n", nazwy[j]);

		// Definicje
		printf("\tDefinicje: \n");
		for (int i = 0; i < ileDef; i++)
		{
			if (strcmp(def[i].nazwa, nazwy[j]) == 0)
			{
				printf("\t\tplik: %s linia: %d\n", def[i].plik, def[i].linia);
				w++;
			}
		}
		if (w == 0)
			printf("\t\tbrak\n");

		w = 0;

		// Prototypy
		printf("\tPrototypy: \n");
		for (int i = 0; i < ileProto; i++)
		{
			if (strcmp(proto[i].nazwa, nazwy[j]) == 0)
			{
				printf("\t\tplik: %s linia: %d\n", proto[i].plik, proto[i].linia);
				w++;
			}
		}

		if (w == 0)
			printf("\t\tbrak\n");

		w = 0;

		// Wywolania
		printf("\tWywolania: \n");
		for (int i = 0; i < ileCall; i++)
		{
			if (strcmp(call[i].nazwa, nazwy[j]) == 0)
			{
				printf("\t\tplik: %s linia: %d\n", call[i].plik, call[i].linia);
				w++;
			}
		}

		if (w == 0)
			printf("\t\tbrak\n");

		w = 0;


		// Uzycia
		printf("\tWywoluje: \n");
		for (int i = 0; i < ileUse; i++)
		{
			if (strcmp(use[i].nazwa, nazwy[j]) == 0)
			{
				printf("\t\t%s (x%d)\n", use[i].plik, use[i].linia);
				w++;
			}
		}

		if (w == 0)
			printf("\t\tbrak\n");

		printf("\n");
	}

	getch();

	return 0;
}