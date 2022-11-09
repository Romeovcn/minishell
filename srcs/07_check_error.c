#include "minishell.h"

int check_not_closed_string(char *str)
{
	char quote_type;
	int quote;

	quote_type = 0;
	quote = 0;
	while (*str)
	{
		if ((*str == '\'' || *str == '\"') && quote == 0)
		{
			quote++;
			quote_type = *str;
		}
		else if (*str == quote_type && quote == 1)
		{
			quote_type = 0;
			quote = 0;
		}
		str++;
	}
	if (quote != 0)
		return (1);
	return (0);
}

int check_redir(t_lexed_list *lexed_list)
{
	if (!lexed_list->next)
		return (printf("No key word after redir\n"), 1);
	if (lexed_list->next->operator != WORD) // Check next is a word
		return (printf("Operator after redir\n"), 1);
}

int check_pipe(t_lexed_list *lexed_list)
{
	if (!lexed_list->next)
		return (printf("No key word after pipe\n"), 1);
	if (lexed_list->next->operator == PIPE) // Check multiple pipe in a row
		return (printf("Double pipe error\n"), 1);
}

int check_error(t_lexed_list *lexed_list)
{
	if (lexed_list->operator == PIPE)
		return (printf("No command before pipe\n"), 1);
	while (lexed_list)
	{
		if (lexed_list->operator == PIPE)
		{
			if (check_pipe(lexed_list))
				return (1);
		}
		else if (lexed_list->operator != PIPE && lexed_list->operator != WORD)
		{
			if (check_redir(lexed_list))
				return (1);
		}
		else if (lexed_list->operator == WORD)
		{
			if (check_not_closed_string(lexed_list->content)) // Check not closed string
				return (printf("Not closed quote error\n"), 1);
		}
		lexed_list = lexed_list->next;
	}
	return (0);
}