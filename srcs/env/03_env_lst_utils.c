/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_env_lst_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/16 22:18:49 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_lst	*lstnew_env(char *name, char *value, t_exec *exec)
{
	t_env_lst	*result;

	result = malloc(sizeof(t_env_lst));
	if (!result) // protect
		return (0);
	result->name = name;
	result->value = value;
	result->next = NULL;
	return (result);
}

t_env_lst	*lstlast_env(t_env_lst *lst)
{
	t_env_lst	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstadd_back_env(t_env_lst **lst, t_env_lst *new)
{
	t_env_lst	*last;

	if (*lst)
	{
		last = lstlast_env(*lst);
		last->next = new;
	}
	else
		*lst = new;
}
