/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_lexer_lst_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/09 17:40:33 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lex_lst	*lstnew_lex(void *content, int operator, t_mal_lst **mal_lst)
{
	t_lex_lst	*result;

	result = malloc(sizeof(t_lex_lst));
	if (!result)
		return (0);
	result->content = content;
	result->operator = operator;
	result->next = NULL;
	lstadd_back_malloc(mal_lst, lstnew_malloc(result->content));
	lstadd_back_malloc(mal_lst, lstnew_malloc(result));
	return (result);
}

t_lex_lst	*lstlast_lexer(t_lex_lst *lst)
{
	t_lex_lst	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstadd_back_lex(t_lex_lst **lst, t_lex_lst *new)
{
	t_lex_lst	*last;

	if (*lst)
	{
		last = lstlast_lexer(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void	read_lst(t_lex_lst *lst)
{
	while (lst)
	{
		printf("type=%d %s\n", lst->operator, lst->content);
		lst = lst->next;
	}
}
