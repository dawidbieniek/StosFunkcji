#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "fun_stack.h"

#pragma warning(disable : 4996)
static struct stack* fun_stack;

int top_of_fun_stack(void)
{
	if (fun_stack == NULL)
		return -1;

	return fun_stack->par_level;
}

void put_on_fun_stack(int par_level, char* fun_name)
{
	struct stack* element = malloc(sizeof(struct stack));

	if (element == NULL)
	{
		fprintf(stderr, "Nie mozna stworzyc stosu!!!");
		return;
	}

	element->funname = malloc(sizeof(char) * strlen(fun_name));
	if (element->funname != NULL)
		strcpy(element->funname, fun_name);

	element->par_level = par_level;
	if (fun_stack == NULL)
		element->next = NULL;
	else
		element->next = fun_stack;

	fun_stack = element;
}

char* get_from_fun_stack(void)
{
	char* funname;

	if (fun_stack == NULL)
		return NULL;

	funname = fun_stack->funname;

	fun_stack = fun_stack->next;

	return funname;
}