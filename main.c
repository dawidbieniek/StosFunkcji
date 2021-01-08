#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "printer.h"
#include "kontener.h"

int main(int argc, char* argv[])
{
	store_init();

	for (int i = 1; i < argc; i++)
		analizatorSkladni(argv[i]);

	wypisz();

	return 0;
}