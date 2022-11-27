/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_exec_simple_manage.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:46:29 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/27 18:35:49 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    here_doc_manage(t_exec *exec)
{
	t_array_lst	*delimiter;

	delimiter = here_doc_delimiter(exec);
	while (delimiter)
	{
		// printf("delimiter: %s\n", delimiter->content);
		here_doc(delimiter->content);
		if (delimiter->next != NULL)
			unlink(delimiter->content);
		else
			exec->here_doc->here_doc = ft_strdup(delimiter->content);
		delimiter = delimiter->next;
	}
	exec->here_doc->fd_last_here_doc = open(exec->here_doc->here_doc, O_RDONLY);
	// unlink(exec->here_doc->here_doc);
	if (exec->nb_command == 1)
		dup2(exec->here_doc->fd_last_here_doc, STDIN_FILENO);
}

void	simple_exec(t_exec *exec)
{
	char		*path;
	char		**arg;

	if (exec->tok_lst->output_fd < 2 && exec->tok_lst->input_fd < 2)
	{
		printf("commande\n");
		command(exec);
	}
	else if (exec->tok_lst->output_fd == 3)
	{
		printf("redirection out\n");
		redir_out(exec);
		if (exec->tok_lst->args != NULL)
			command(exec);
	}
	else if (exec->tok_lst->input_fd == 2)
	{
		printf("redirection in\n");
		redir_in(exec);
		if (exec->tok_lst->args != NULL)
			command(exec);
	}
	else if (exec->tok_lst->input_fd == 4)
	{
		printf("here_doc\n");
		if (exec->tok_lst->args != NULL)
			command(exec);
	}
	else if (exec->tok_lst->output_fd == 5)
	{
		printf("append\n");
		append(exec);
		if (exec->tok_lst->args != NULL)
			command(exec);
	}
}