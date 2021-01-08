#ifndef _KONTENER_H_IS_INCLUDED_
#define _KONTENER_H_IS_INCLUDED_

struct FuncInfo
{
	char* nazwa;
	int linia;
	char* plik;
} typedef funcInfo;

char** nazwy;		// lista nazw funkcji
int ileNazw;		// liczba nazw w liscie

funcInfo* def;		// lista definicji funkcji
int ileDef;			// liczba elementow listy definicji funkcji
funcInfo* proto;	// lista prototypow funkcji
int ileProto;		// liczba elementow listy prototypow funkcji
funcInfo* call;		// lista wywolan funkcji
int ileCall;		// liczba elementow listy wywolan funkcji
funcInfo* use;		// lista uzyc funkcji
int ileUse;			// liczba elementow listy uzyc funkcji

char* ostatniaNazwaDefinicji;

void store_init();
void dodajNazwe(char* nazwa);
void store_add_def(char* nazwa, int linia, char* plik);
void store_add_proto(char* nazwa, int linia, char* plik);
void store_add_call(char* nazwa, int linia, char* plik);
void store_add_use(char* nazwa);

#endif