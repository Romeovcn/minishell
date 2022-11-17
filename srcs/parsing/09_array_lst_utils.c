/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_array_lst_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/09 18:04:30 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_array_lst	*lstnew_array(char *content, t_mal_lst **mal_lst)
{
	t_array_lst	*result;

	result = malloc(sizeof(t_array_lst));
	if (!result)
		return (0);
	result->content = content;
	result->next = NULL;
	lstadd_back_malloc(mal_lst, lstnew_malloc(result));
	return (result);
}

t_array_lst	*lstlast_array(t_array_lst *lst)
{
	t_array_lst	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstadd_back_array(t_array_lst **lst, t_array_lst *new)
{
	t_array_lst	*last;

	if (*lst)
	{
		last = lstlast_array(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void	read_lst_array(t_array_lst *lst, char *type)
{
	printf("%s:", type);
	while (lst)
	{
		printf(" %s", lst->content);
		lst = lst->next;
	}
	printf("\n");
}