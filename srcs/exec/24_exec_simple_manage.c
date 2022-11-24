/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_exec_simple_manage.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:46:29 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/24 16:54:21 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    here_doc_manage(t_exec *exec)
{
    t_array_lst *tmp;
    char        *last_heredoc;
    int         last_heredoc_fd;

    printf("here_doc\n");
    tmp = exec->tok_lst->delimiter;
    while (tmp)
    {
        here_doc(tmp->content);
        if (tmp->next != NULL)
            unlink(tmp->content);
        else
            last_heredoc = ft_strdup(tmp->content);
        tmp = tmp->next;
    }
    last_heredoc_fd = open(last_heredoc, O_RDONLY);
    unlink(last_heredoc);
    dup2(last_heredoc_fd, STDIN_FILENO);
    if (exec->tok_lst->args != NULL)
        command(exec);
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
		printf("input : %d\n", exec->tok_lst->input_fd);
		if (exec->tok_lst->input_fd == 4)
		{
            // heredoc
		}
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
        here_doc_manage(exec);
	else if (exec->tok_lst->output_fd == 5)
	{
		printf("append\n");
		append(exec);
		if (exec->tok_lst->args != NULL)
			command(exec);
	}
}