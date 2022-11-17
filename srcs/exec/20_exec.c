#include "minishell.h"

void test(void)
{
	printf("test");
}

void exec(t_tok_lst *tok_lst)
{
	char **args;

	while (tok_lst)
	{
		
		tok_lst = tok_lst->next;
	}
}