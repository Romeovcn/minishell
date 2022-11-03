# include "minishell.h"

int	is_operator(char *readline_str)
{
	if (readline_str[1] && readline_str[0] == '<' && readline_str[1] == '<')
		return (1);
	if (readline_str[1] && readline_str[0] == '>' && readline_str[1] == '>')
		return (1);
	if (readline_str[0] == '|')
		return (1);
	if (readline_str[0] == '<') 
		return (1);
	if (readline_str[0] == '>')
		return (1);
	return (0);
}

int get_word_size(char *readline_str)
{
	int i;
	int quote;
	char quote_type;

	i = 0;
	quote = 0;
	quote_type = 0;
	while (*readline_str)
	{
		if (quote == 0 && is_operator(readline_str))
			break ;
		if ((*readline_str == ' ' || *readline_str == '\t') && quote == 0)
			break ;
		if ((*readline_str == '\'' || *readline_str == '\"') && quote == 0)
		{
			quote++;
			quote_type = *readline_str;
		}
		else if (quote == 1 && *readline_str == quote_type)
		{
			quote = 0;
			quote_type = 0;
		}
		i++;
		readline_str++;
	}
	return (i);
}

void get_word(char *readline_str, char **word)
{
	int i;
	int quote;
	char quote_type;

	i = 0;
	quote = 0;
	quote_type = 0;
	while (*readline_str)
	{
		if (quote == 0 && is_operator(readline_str))
			break ;
		if ((*readline_str == ' ' || *readline_str == '\t') && quote == 0)
			break ;
		if ((*readline_str == '\'' || *readline_str == '\"') && quote == 0)
		{
			quote++;
			quote_type = *readline_str;
		}
		else if (quote == 1 && *readline_str == quote_type)
		{
			quote = 0;
			quote_type = 0;
		}
		(*word)[i] = *readline_str;
		i++;
		readline_str++;
	}
	(*word)[i] = 0;
}

void go_to_word_end(char **readline_str)
{
	int quote;
	char quote_type;

	quote = 0;
	quote_type = 0;
	while (**readline_str)
	{
		if (quote == 0 && is_operator(*readline_str))
			break ;
		if ((**readline_str == ' ' || **readline_str == '\t') && quote == 0)
			break ;
		if ((**readline_str == '\'' || **readline_str == '\"') && quote == 0)
		{
			quote++;
			quote_type = **readline_str;
		}
		else if (quote == 1 && **readline_str == quote_type)
		{
			quote = 0;
			quote_type = 0;
		}
		(*readline_str)++;
	}
}
