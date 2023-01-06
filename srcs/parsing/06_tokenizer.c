/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/09 19:26:26 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok_lst	*get_token_lst(t_exec *exec)
{
	t_tok_lst	*token;
	t_tok_lst	*head;
	t_lex_lst *lex_lst = exec->lex_lst;
	t_mal_lst **mal_lst = &exec->mal_lst;

	token = NULL;
	lstadd_back_token(&token, lstnew_token(exec));
	head = token;
	while (lex_lst)
	{
		if (lex_lst->operator == PIPE)
		{
			lstadd_back_token(&token, lstnew_token(exec));
			token = token->next;
			lex_lst = lex_lst->next;
		}
		else if (lex_lst->operator == HERE_DOC)
			add_here_doc(&token, &lex_lst, mal_lst);
		else if (lex_lst->operator == REDIR_IN)
			add_redir_in(&token, &lex_lst, mal_lst);
		else if (lex_lst->operator == REDIR_OUT)
			add_redir_out(&token, &lex_lst, mal_lst);
		else if (lex_lst->operator == APP_OUT)
			add_app_out(&token, &lex_lst, mal_lst);
		else if (lex_lst->operator == WORD)
			add_word(&token, &lex_lst, mal_lst);
	}
	return (head);
}
