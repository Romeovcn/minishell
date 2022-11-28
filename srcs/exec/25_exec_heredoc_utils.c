/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_exec_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:50:56 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/27 17:53:22 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_array_lst	*get_here_doc_lst(t_exec *exec)
{
	t_tok_lst	*tmp;
	t_array_lst	*tmp_del;
	t_array_lst	*delimiter;
	int			i;

	delimiter = NULL;
	tmp = exec->tok_lst;
	i = 0;
	while (i < exec->nb_command)
	{
		tmp_del = tmp->delimiter;
		while (tmp_del)
		{
			lstadd_back_array(&delimiter, lstnew_array(tmp_del->content, &exec->mal_lst));
			tmp_del = tmp_del->next;
		}
		i++;
		tmp = tmp->next;
	}
	return (delimiter);
}

int	check_heredoc(t_exec *exec)
{
	t_tok_lst	*tmp;
	int			i;

	tmp = exec->tok_lst;
	i = 0;
	while (i < exec->nb_command)
	{
		if (tmp->input_fd == HERE_DOC)
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
