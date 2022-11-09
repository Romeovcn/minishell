#include "minishell.h"

int is_env(char *str)
{
	int i;

	i = 0;
	if (str[i] != '$' || !str[i + 1])
		return 0;
	if (str[i + 1] != '\'' && str[i + 1] != '\"')
		return 1;
	return 0;
}

char *get_env_name(char *str, t_malloc_list **malloc_lst)
{
	int size;
	int i;
	char *env_name;

	i = 0;
	while (str[i])
	{
		if (isspace(str[i]) || str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	env_name = malloc((i + 1) * sizeof(char));
	if (!env_name)
		return NULL;
	// ft_lstadd_back_malloc(malloc_lst, ft_lstnew_malloc(env_name));
	i = 0;
	while (*str)
	{
		if (isspace(*str) || *str == '\'' || *str == '\"')
			break ;
		env_name[i] = *str;
		i++;
		str++;
	}
	env_name[i] = 0;
	return (env_name);
}

void go_end_env_name(char **str)
{
	while (**str)
	{
		if (isspace(**str) || **str == '\'' || **str == '\"')
			break ;
		(*str)++;
	}
}

void	parse_env(char **str, t_malloc_list **malloc_lst, t_env_list *env_lst, char **result)
{
	char *env_name;
	char *env_value;
	
	(*str)++;
	env_name =  get_env_name(*str, malloc_lst);
	env_value =  get_env_value(env_name, env_lst);
	// printf("ENV NAME = %s\n", env_name);
	// printf("ENV VALUE = %s\n", env_value);
	*result = ft_strjoin(*result, env_value);
	ft_lstadd_back_malloc(malloc_lst, ft_lstnew_malloc(*result));
	go_end_env_name(str);
	free(env_name);
}

char	*parse_quote_env(char *str, t_malloc_list **malloc_lst, t_env_list *env_lst)
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
			parse_env(&str, malloc_lst, env_lst, &result);
		else
			result = ft_strjoin_char(result, *str++, malloc_lst);
	}
	return (result);
}

void parsing(t_lexed_list *lexer_lst, t_malloc_list **malloc_lst, t_env_list *env_lst)
{
	while (lexer_lst)
	{
		if (lexer_lst->operator == WORD)
			lexer_lst->content = parse_quote_env(lexer_lst->content, malloc_lst, env_lst);
		lexer_lst = lexer_lst->next;
	}
}