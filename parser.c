#include <stdio.h>
#include <stdlib.h>		// exit - ale exit trzeba kiedyś usunąć i nie będzie to potrzebne

#include "parser.h"

#include "alex.h"       // analizator leksykalny
#include "fun_stack.h"  // stos funkcji
#include "kontener.h"

#pragma warning(disable : 4996) // fopen

void analizatorSkladni(char* inpname)	// przetwarza plik inpname
{                               
	FILE* in = fopen(inpname, "r");
	if (in == NULL)
	{
		fprintf(stderr, "Nie mozna otworzyc pliku %s!!!", inpname);
		return;
	}

	int nbra = 0;   // bilans nawiasów klamrowych {}
	int npar = 0;   // bilans nawiasów zwykłych ()

	alex_init4file(in);          // ustaw analizator leksykalny, aby czytał in
	
	lexem_t lex;

	lex = alex_nextLexem();      // pobierz następny leksem
	while (lex != EOFILE)
	{
		switch (lex)
		{
		case IDENT:
		{
			char* iname = alex_ident();			// zapamiętaj identyfikator i patrz co dalej
			lexem_t nlex = alex_nextLexem();	// nawias otwierający - to zapewne funkcja
			if (nlex == OPEPAR)
			{
				npar++;
				put_on_fun_stack(npar, iname);        // odłóż na stos funkcji
													  // stos f. jest niezbędny, aby poprawnie obsłużyć sytuacje typu
													  // f1( 5, f2( a ), f3( b ) )
			}
			else								// nie nawias, czyli nie funkcja
			{
				lex = nlex;
				continue;
			}
		}
		break;
		case OPEPAR:
			npar++;
			break;
		case CLOPAR:							// zamykający nawias - to może być koniec prototypu, nagłówka albo wywołania
		{
			if (top_of_fun_stack() == npar)		// sprawdzamy, czy liczba nawiasów bilansuje się z wierzchołkiem stosu funkcji
			{									// jeśli tak, to właśnie wczytany nawias jest domknięciem nawiasu otwartego
												// za identyfikatorem znajdującym się na wierzchołku stosu
				lexem_t nlex = alex_nextLexem();     // bierzemy nast leksem
				if (nlex == OPEBRA)   // nast. leksem to klamra a więc mamy do czynienia z def. funkcji
				{
					store_add_def(get_from_fun_stack(), alex_getLN(), inpname);
					nbra++;						// trzeba zwiekszyc nbra (program omija tu znak {)
				}
				else if (nbra == 0)   // nast. leksem to nie { i jesteśmy poza blokami - to musi być prototyp
										// Bedzie dzialalo gdy { jest w nowej linii ???
					store_add_proto(get_from_fun_stack(), alex_getLN(), inpname);
				else                  // nast. leksem to nie { i jesteśmy wewnątrz bloku - to zapewne wywołanie
				{
					char* nazwa = get_from_fun_stack();
					store_add_call(nazwa, alex_getLN(), inpname);
					store_add_use(nazwa);
				}
			}
			npar--;
		}
		break;
		case OPEBRA:
			nbra++;
			break;
		case CLOBRA:
			nbra--;
			break;
		case ERROR:
		{
			fprintf(stderr, "\nBUUUUUUUUUUUUUUUUUUUUUU!\n"
				"W pliku %s (linia %d) są błędy składni.\n"
				"Kończę!\n\n", inpname, alex_getLN());
			exit(1);               // to nie jest najlepsze, ale jest proste ;-)
		}
		break;
		default:
			break;
		}
		lex = alex_nextLexem();
	}
}