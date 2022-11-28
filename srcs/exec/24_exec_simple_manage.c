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
	t_array_lst	*tmp_here_doc_lst;

	exec->here_doc_lst = get_here_doc_lst(exec);
	tmp_here_doc_lst = exec->here_doc_lst;
	while (tmp_here_doc_lst)
	{
		here_doc(tmp_here_doc_lst->content);
		tmp_here_doc_lst = tmp_here_doc_lst->next;
	}
}

void	simple_exec(t_exec *exec, int i)
{
	char		*path;
	char		**arg;

	if (exec->tok_lst->output_fd == REDIR_OUT)
		redir_out(exec);
	if (exec->tok_lst->input_fd == REDIR_IN)
	{
		printf("redirection in\n");
		redir_in(exec);
	}
	if (exec->tok_lst->input_fd == HERE_DOC)
	{
		int fd_here_doc = open(lstlast_array(exec->tok_lst->delimiter)->content, O_RDONLY);
		dup2(fd_here_doc, STDIN_FILENO);
		// printf("here_doc\n");
	}
	// if (exec->tok_lst->output_fd == APP_OUT)
	// {
	// 	// printf("append\n");
	// 	append(exec);
	// }
	if (exec->tok_lst->args != NULL)
		command(exec, i);
	exit(0);
}