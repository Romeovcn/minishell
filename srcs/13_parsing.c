#include "minishell.h"

int is_env(char *str, int i)
{
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

// char *manage_env()
// {

// }

char *manage_quotes(char *str, t_malloc_list **malloc_lst, t_env_list *env_lst)
{
	int i;
	int quote;
	char quote_type;
	char *result;

	i = 0;
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
		else if (quote_type != '\'' && is_env(str, i))
		{
			str++;
			printf("ENV NAME = %s\n", get_env_name(str, malloc_lst));
			// printf("ENV VALUE = %s\n", get_env_value(get_env_name(str, i + 1, malloc_lst) , env_lst));

			// result = ft_strjoin(result, get_env_value(get_env_name(str, malloc_lst) , env_lst));
			// ft_lstadd_back_malloc(malloc_lst, ft_lstnew_malloc(result));
			// while (*str)
			// {
			// 	if (isspace(*str) || *str == '\'' || *str == '\"')
			// 		break ;
			// 	str++;
			// }
			break ;
		}
		else
		{
			result = ft_strjoin_char(result, *str);
			ft_lstadd_back_malloc(malloc_lst, ft_lstnew_malloc(result));
			str++;
		}
	}
	return result;
}

void parsing(t_lexed_list *lexer_lst, t_malloc_list **malloc_lst, t_env_list *env_lst)
{
	while (lexer_lst)
	{
		if (lexer_lst->operator == WORD)
		{
			// printf("---------------------\n");
			lexer_lst->content = manage_quotes(lexer_lst->content, malloc_lst, env_lst);
			// printf("\n---------------------\n");
		}
		lexer_lst = lexer_lst->next;
	}
}