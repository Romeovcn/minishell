#include "minishell.h"

void	parse_env(char **str, t_mal_lst **mal_lst, t_env_lst *env_lst, char **result)
{
	char *env_name;
	char *env_value;
	
	(*str)++;
	env_name =  get_env_name(*str, mal_lst);
	env_value =  get_env_value(env_name, env_lst);
	// printf("ENV NAME = %s\n", env_name);
	// printf("ENV VALUE = %s\n", env_value);
	*result = ft_strjoin(*result, env_value);
	if (!*result)
	{
		free_lst_malloc(*mal_lst);
		exit (1);
	}
	lstadd_back_malloc(mal_lst, lstnew_malloc(*result));
	go_end_env_name(str);
	free(env_name);
}

char	*parse_quote_env(char *str, t_mal_lst **mal_lst, t_env_lst *env_lst)
{
	int quote;
	char quote_type;
	char *result;

	quote = 0;
	quote_type = 0;
	result = "";
	while (*str)
	{
		if ((*str == '\'' || *str == '\"') && quote == 0)
		{
			quote++;
			quote_type = *str;
			str++;
		}
		else if (*str == quote_type && quote == 1)
		{
			quote = 0;
			quote_type = 0;
			str++;
		}
		else if (quote_type != '\'' && is_env(str))
			parse_env(&str, mal_lst, env_lst, &result);
		else
			result = strjoin_char(result, *str++, mal_lst);
	}
	return (result);
}

void parser(t_lex_lst *lex_lst, t_mal_lst **mal_lst, t_env_lst *env_lst)
{
	t_lex_lst *head = lex_lst;
	while (lex_lst)
	{
		if (lex_lst->operator == WORD)
			lex_lst->content = parse_quote_env(lex_lst->content, mal_lst, env_lst);
		lex_lst = lex_lst->next;
	}
	printf("--------Command lst lexed after parsing--------\n");
	read_lst(head);
}