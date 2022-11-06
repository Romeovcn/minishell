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
		return (printf("Syntax error\n"), 1);
	return (0);
}

int check_error(t_lexed_list *lexed_list)
{
	while (lexed_list)
	{
		if (check_not_closed_string(lexed_list->content))
			return (printf("Not closed quote error\n"), 1);
		if (lexed_list->next && lexed_list->operator == PIPE && lexed_list->next->operator == PIPE)
			return (printf("Double pipe error\n"), 1);
		if (lexed_list->next && lexed_list->operator != 0 && lexed_list->next->operator != 0)
			return (printf("Double redir error\n"), 1);
		lexed_list = lexed_list->next;
	}
}