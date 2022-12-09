/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_lexer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/09 16:27:03 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_operator(char **rl_str, t_lex_lst **lex_lst, t_mal_lst **mal_lst)
{
	if ((*rl_str)[1] && (*rl_str)[0] == '<' && (*rl_str)[1] == '<')
	{
		lstadd_back_lex(lex_lst, lstnew_lex(ft_strdup("<<"), HERE_DOC, mal_lst));
		(*rl_str)++;
	}
	else if ((*rl_str)[1] && (*rl_str)[0] == '>' && (*rl_str)[1] == '>')
	{
		lstadd_back_lex(lex_lst, lstnew_lex(ft_strdup(">>"), APP_OUT, mal_lst));
		(*rl_str)++;
	}
	else if ((*rl_str)[0] == '|')
		lstadd_back_lex(lex_lst, lstnew_lex(ft_strdup("|"), PIPE, mal_lst));
	else if ((*rl_str)[0] == '<')
		lstadd_back_lex(lex_lst, lstnew_lex(ft_strdup("<"), REDIR_IN, mal_lst));
	else if ((*rl_str)[0] == '>')
		lstadd_back_lex(lex_lst, lstnew_lex(ft_strdup(">"), REDIR_OUT, mal_lst));
	(*rl_str)++;
}

void	manage_word(char *rl_str, t_lex_lst **lex_lst, t_mal_lst **mal_lst)
{
	char	*word;
	int		size;

	size = get_word_size(rl_str);
	word = malloc((size + 1) * sizeof(char));
	if (!word)
		exit(1);
	get_word(rl_str, &word);
	lstadd_back_lex(lex_lst, lstnew_lex(word, WORD, mal_lst));
}

t_lex_lst	*lexer(char *rl_str, t_mal_lst **mal_lst)
{
	t_lex_lst	*lex_lst;

	lex_lst = NULL;
	while (*rl_str)
	{
		if (is_operator(rl_str))
			manage_operator(&rl_str, &lex_lst, mal_lst);
		else if (!ft_isspace(*rl_str) && !is_operator(rl_str))
		{
			manage_word(rl_str, &lex_lst, mal_lst);
			go_to_word_end(&rl_str);
		}
		else
			rl_str++;
	}
	// printf("--------Command lst lexed--------\n");
	// read_lst(lex_lst);
	return (lex_lst);
}
