#ifndef _FUN_STACK_H_IS_INCLUDED_
#define _FUN_STACK_H_IS_INCLUDED_

struct stack
{
	char* funname;
	int par_level;
	struct stack* next;
};

int top_of_fun_stack(void);  // zwraca par_level - "zagłębienie nawiasowe" przechowywane na szczycie
void put_on_fun_stack(int par_level, char* funame); // odkłada na stos parę (funame,par_level)
char* get_from_fun_stack(void); // usuwa z wierzchołka parę (funame,par_level), zwraca zdjętą funame

#endif
