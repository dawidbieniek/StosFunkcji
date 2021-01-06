#ifndef _KON__DANYCH_H_IS_INCLUDED_
#define _KON__DANYCH_H_IS_INCLUDED_

struct FuncInfo
{
	char* nazwa;
	int linia;
	char* plik;
} typedef info;

void dodajNazwe(char* nazwa);

void store_add_def(char* nazwa, int linia, char* plik);
void store_add_proto(char* nazwa, int linia, char* plik);
void store_add_call(char* nazwa, int linia, char* plik);

void Wypisz();
#endif