/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_tokenizer_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/13 23:23:20 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void add_here_doc(t_tok_lst **token, t_lex_lst **lex_lst, t_mal_lst **mal_lst)
{
	(*token)->input_fd = HERE_DOC;
	*lex_lst = (*lex_lst)->next;
	lstadd_back_array(&(*token)->delimiter, lstnew_array((*lex_lst)->content, mal_lst));
	*lex_lst = (*lex_lst)->next;
}

void add_redir_in(t_tok_lst **token, t_lex_lst **lex_lst, t_mal_lst **mal_lst)
{
	(*token)->input_fd = REDIR_IN;
	*lex_lst = (*lex_lst)->next;
	lstadd_back_array(&(*token)->in_file, lstnew_array((*lex_lst)->content, mal_lst));
	*lex_lst = (*lex_lst)->next;
}

void add_redir_out(t_tok_lst **token, t_lex_lst **lex_lst, t_mal_lst **mal_lst)
{
	(*token)->output_fd = REDIR_OUT;
	*lex_lst = (*lex_lst)->next;
	lstadd_back_array(&(*token)->out_file, lstnew_array((*lex_lst)->content, mal_lst));
	*lex_lst = (*lex_lst)->next;
}

void add_app_out(t_tok_lst **token, t_lex_lst **lex_lst, t_mal_lst **mal_lst)
{
	(*token)->output_fd = APP_OUT;
	*lex_lst = (*lex_lst)->next;
	lstadd_back_array(&(*token)->out_file, lstnew_array((*lex_lst)->content, mal_lst));
	*lex_lst = (*lex_lst)->next;
}

void add_word(t_tok_lst **token, t_lex_lst **lex_lst, t_mal_lst **mal_lst)
{
	lstadd_back_array(&(*token)->args, lstnew_array((*lex_lst)->content, mal_lst));
	*lex_lst = (*lex_lst)->next;
}