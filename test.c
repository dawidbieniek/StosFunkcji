#include <stdio.h>

#include "fun_stack.h"

int main()
{
	char* test = "abcdefghijklmnopqrstuvwxyz";

	int i;

	printf("wrzucanie elementow na stos\n");
	for (i = 0; i < 26; i++)
	{
		put_on_fun_stack(i, test + i);
		printf("%d\n", top_of_fun_stack());
		printf("%s\n", test + i);
	}

	printf("Zrzucanie ze stosu\n");

	for (i = 0; i < 26; i++)
	{
		printf("%d\n", top_of_fun_stack());
		printf("%s\n", get_from_fun_stack());
	}

	getch();
}