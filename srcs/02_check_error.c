/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_check_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/06 23:33:05 by jsauvage         ###   ########.fr       */
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
		return (ft_putstr_fd("bash: syntax error: not closed quote ici\n", 2), 1);
	return (0);
}

int	check_redir(t_lex_lst *lexed_list)
{
	if (!lexed_list->next)
		return (ft_putstr_fd("bash: syntax error: no key word after redir\n", 2), 1);
	if (lexed_list->next->operator != WORD)
		return (ft_putstr_fd("bash: syntax error: operator after redir\n", 2), 1);
	return (0);
}

int	check_pipe(t_lex_lst *lexed_list)
{
	if (!lexed_list->next)
		return (ft_putstr_fd("bash: syntax error: no word after pipe\n", 2), 1);
	if (lexed_list->next->operator == PIPE)
		return (ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2), 1);
	return (0);
}

int	check_error(t_lex_lst *lexed_list)
{
	if (lexed_list->operator == PIPE)
		return (ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2), G_STATUS = 2, 2);
	while (lexed_list)
	{
		if (lexed_list->operator == PIPE)
		{
			if (check_pipe(lexed_list))
				return (G_STATUS = 1, 1);
		}
		else if (lexed_list->operator != PIPE && lexed_list->operator != WORD)
		{
			if (check_redir(lexed_list))
				return (G_STATUS = 2, 1);
		}
		else if (lexed_list->operator == WORD)
		{
			if (check_not_closed_string(lexed_list->content))
				return (G_STATUS = 1, 1);
		}
		lexed_list = lexed_list->next;
	}
	return (0);
}
