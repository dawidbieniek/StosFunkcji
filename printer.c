#include <stdio.h>

#include "printer.h"

#include "kontener.h"

void Wypisz()
{
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
}