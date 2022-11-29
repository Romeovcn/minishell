/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_exec_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:46:29 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/29 16:12:25 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    here_doc_manage(t_exec *exec)
{
	t_array_lst	*tmp_heredoc_lst;

	exec->here_doc_lst = get_here_doc_lst(exec);
	tmp_heredoc_lst = exec->here_doc_lst;
	while (tmp_heredoc_lst)
	{
		get_here_doc_file(tmp_heredoc_lst->content, tmp_heredoc_lst->content2);
		tmp_heredoc_lst = tmp_heredoc_lst->next;
	}
}

void	command(t_exec *exec, int i)
{
	char	**args;
	char	*path;

	path = find_right_access(getenv("PATH"), exec->tok_lst->args);
	args = lst_to_str_array(exec->tok_lst->args, &exec->mal_lst);
	if (exec->tok_lst->output_fd == 1 && i != exec->nb_command - 1)
		dup2(exec->fd[1], STDOUT_FILENO);
	close_fd(exec->fd[0], exec->fd[1]);
	execve(path, args, exec->envp);
	exit(0);
}

void	exec_token(t_exec *exec, int i)
{
	if (exec->tok_lst->output_fd == REDIR_OUT)
		redir_out(exec->tok_lst);
	if (exec->tok_lst->input_fd == REDIR_IN)
		redir_in(exec->tok_lst);
	if (exec->tok_lst->input_fd == HERE_DOC)
		here_doc(exec->tok_lst);
	if (exec->tok_lst->output_fd == APP_OUT)
		append(exec->tok_lst);
	if (exec->tok_lst->args != NULL)
		command(exec, i);
	exit(0);
}