/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/17 17:02:59 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tok_lst	*get_token_lst(t_lex_lst *lex_lst, t_mal_lst **mal_lst)
{
	t_tok_lst	*token;
	t_tok_lst	*head;

	token = NULL;
	lstadd_back_token(&token, lstnew_token(mal_lst));
	head = token;
	// printf("--------Command lst token--------\n");
	head = token;
	while (lex_lst)
	{
		if (lex_lst->operator == PIPE)
		{
			read_lst_array(token->args, "args");
			printf("intput_fd: %d\n", token->input_fd);
			read_lst_array(token->delimiter, "delimiter");
			read_lst_array(token->in_file, "in_file");
			printf("output_fd: %d\n", token->output_fd);
			read_lst_array(token->out_file, "out_file");
			printf("-----------------\n");
			lstadd_back_token(&token, lstnew_token(mal_lst));
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
	read_lst_array(token->args, "args");
	printf("intput_fd: %d\n", token->input_fd);
	read_lst_array(token->delimiter, "delimiter");
	read_lst_array(token->in_file, "in_file");
	printf("output_fd: %d\n", token->output_fd);
	read_lst_array(token->out_file, "out_file");
	printf("-----------------\n");
	return (head);
}
