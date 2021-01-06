#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "alex.h"
#include "fun_stack.h"

static int ln = 0;
static char ident[256];
static FILE* ci = NULL;

static int ignore = 0;		// 0 - analizuj znaki; 1 - ignoruj do napotkania \n; 2 - ignoruj do napotkana */ 

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
		if (ignore == 0)			// analizuj znaki
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
				while ((c = fgetc(ci)) != '"')	// ignoruj znaki do napotkania "
				{
					if (c == '\n')
						ln++;
					else if (c == EOF)
						return EOFILE;
				}
			}
			else if (c == '\'')
			{
				while ((c = fgetc(ci)) != '\'')	// ignoruj znaki do napotkania '
				{
					if (c == '\n')
						ln++;
					else if (c == EOF)
						return EOFILE;
				}
			}
			else if (c == '/')
			{
				if ((c = fgetc(ci)) != EOF)
				{
					if (c == '/')				// komentarz liniowy
						ignore = 1;
					else if (c == '*')			// komentarz blokowy
						ignore = 2;
				}
				else
					return EOFILE;
			}
			else if (isdigit(c) || c == '.')
			{
				continue;			// dla czytelnosci
			}
			else
			{
				return OTHER;
			}
		}
		else if (ignore == 1)		// ignoruj do napotkania \n
		{
			if (c == '\n')
				ignore = 0;
		}
		else if (ignore == 2)		// ignoruj do napotkania */
		{
			if (c == '*')
			{
				if ((c = fgetc(ci)) != EOF)
				{
					if (c == '/')
						ignore = 0;
				}
				else
					return EOFILE;
			}
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
	if (strcmp(ident, "auto") == 0) return 1;
	if (strcmp(ident, "break") == 0) return 1;
	if (strcmp(ident, "case") == 0) return 1;
	if (strcmp(ident, "const") == 0) return 1;
	if (strcmp(ident, "continue") == 0) return 1;
	if (strcmp(ident, "default") == 0) return 1;
	if (strcmp(ident, "do") == 0) return 1;
	if (strcmp(ident, "double") == 0) return 1;
	if (strcmp(ident, "else") == 0) return 1;
	if (strcmp(ident, "enum") == 0) return 1;
	if (strcmp(ident, "extern") == 0) return 1;
	if (strcmp(ident, "dloat") == 0) return 1;
	if (strcmp(ident, "for") == 0) return 1;
	if (strcmp(ident, "goto") == 0) return 1;
	if (strcmp(ident, "if") == 0) return 1;
	if (strcmp(ident, "long") == 0) return 1;
	if (strcmp(ident, "register") == 0) return 1;
	if (strcmp(ident, "short") == 0) return 1;
	if (strcmp(ident, "signed") == 0) return 1;
	if (strcmp(ident, "sizeof") == 0) return 1;
	if (strcmp(ident, "static") == 0) return 1;
	if (strcmp(ident, "struct") == 0) return 1;
	if (strcmp(ident, "switch") == 0) return 1;
	if (strcmp(ident, "typedef") == 0) return 1;
	if (strcmp(ident, "union") == 0) return 1;
	if (strcmp(ident, "unsigned") == 0) return 1;
	if (strcmp(ident, "votalite") == 0) return 1;
	if (strcmp(ident, "while") == 0) return 1;
	if (strcmp(ident, "int") == 0) return 1;
	if (strcmp(ident, "char") == 0) return 1;
	if (strcmp(ident, "return") == 0) return 1;
	return 0;
}