#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "printer.h"

int main(int argc, char* argv[])
{
	store_init();

	for (int i = 1; i < argc; i++)
		analizatorSkladni(argv[i]);

	Wypisz();
	getch();

	return 0;
}