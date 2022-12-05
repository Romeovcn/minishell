/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/13 03:10:29 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_not_closed_string(char *str)
{
	char	quote_type;
	int		quote;

	quote = 0;
	quote_type = 0;
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
		return (printf("Not closed quote error\n"), 1);
	return (0);
}

int	check_redir(t_lex_lst *lexed_list)
{
	if (!lexed_list->next)
		return (printf("No key word after redir\n"), 1);
	if (lexed_list->next->operator != WORD)
		return (printf("Operator after redir\n"), 1);
	return (0);
}

int	check_pipe(t_lex_lst *lexed_list)
{
	if (!lexed_list->next)
		return (printf("No key word after pipe\n"), 1);
	if (lexed_list->next->operator == PIPE)
		return (printf("Double pipe error\n"), 1);
	return (0);
}

int	check_error(t_lex_lst *lexed_list)
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
			if (check_not_closed_string(lexed_list->content))
				return (1);
		}
		lexed_list = lexed_list->next;
	}
	return (0);
}
