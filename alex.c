#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "alex.h"
#include "fun_stack.h"

static int ln = 0;
static char ident[256];
static FILE* ci = NULL;

void alex_init4file(FILE* in)
{
	ln = 1;
	ci = in;
}

lexem_t alex_nextLexem(void)
{
	char c;
	while ((c = fgetc(ci)) != EOF)
	{
		if (isspace(c))
		{
			if (c == '\n')
				ln++;
			continue;
		}
		else if (c == '(')
			return OPEPAR;
		else if (c == ')')
			return CLOPAR;
		else if (c == '{')
			return OPEBRA;
		else if (c == '}')
			return CLOBRA;
		else if (isalpha(c))
		{
			int i = 1;
			ident[0] = c;
			while (isalnum(c = fgetc(ci)))
				ident[i++] = c;
			ident[i] = '\0';
			fseek(ci, -1, SEEK_CUR);	// Cofniecie o 1 pozycje do tylu (jesli tego nie ma to omija znaki)
			return isKeyword(ident) ? OTHER : IDENT;
		}
		else if (c == '"')
		{
			/* Uwaga: tu trzeba jeszcze poprawic obsluge nowej linii w trakcie napisu
			   i \\ w napisie
			*/
			int cp = c;
			while ((c = fgetc(ci)) != EOF && c != '"' && cp == '\\')
			{
				cp = c;
			}
			return c == EOF ? EOFILE : OTHER;
		}
		else if (c == '/')
		{
			/* moze byc komentarz */
		} if (isdigit(c) || c == '.') 
		{
			/* liczba */
		}
		else
		{
			return OTHER;
		}
	}
	return EOFILE;
}

char* alex_ident(void)
{
	return ident;
}

int alex_getLN()
{
	return ln;
}

int isKeyword(char* ident)
{
	if (strcmp(ident, "void") == 0) return 1;
	if (strcmp(ident, "int") == 0) return 1;
	if (strcmp(ident, "return") == 0) return 1;
	return 0;
}