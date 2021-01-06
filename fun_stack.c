#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fun_stack.h"

#pragma warning(disable : 4996)

static struct stack* fun_stack;		// stos funkcji

int top_of_fun_stack(void)			// zwraca poziom nawiasow elemento z gory stosu
{
	if (fun_stack == NULL)
		return -1;

	return fun_stack->par_level;
}

void put_on_fun_stack(int par_level, char* fun_name)	// dodaje element na gore stosu
{
	struct stack* element = malloc(sizeof(struct stack));	// rezerwowanie pamieci na stos
	if (element == NULL)
	{
		fprintf(stderr, "Nie mozna stworzyc stosu!!!");
		return;
	}

	element->funname = malloc(sizeof(char) * strlen(fun_name));	// dodawanie nazwy do elementu
	if (element->funname != NULL)
		strcpy(element->funname, fun_name);

	element->par_level = par_level;								// dodawanie poziomu nawiasow do elementu

	if (fun_stack == NULL)										// wrzucanie elementu na gore stosu
		element->next = NULL;
	else
		element->next = fun_stack;

	fun_stack = element;										
}

char* get_from_fun_stack(void)		// zwraca nazwe elementu na gorze stosu i go zrzuca
{
	char* funname;

	if (fun_stack == NULL)
		return NULL;

	funname = fun_stack->funname;	// kopiowanie nazwy elementu

	fun_stack = fun_stack->next;	

	return funname;
}