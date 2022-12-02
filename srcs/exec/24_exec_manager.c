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

void	command(t_exec *exec, int i)
{
	char	**args;
	char	*path;

	args = lst_to_str_array(exec->tok_lst->args, exec->mal_lst);
	if (is_built_in(args[0]))
		exit(exec_built_in(exec->tok_lst, 0, exec->mal_lst, exec->env_lst));
	path = find_right_access(getenv("PATH"), exec->tok_lst->args);
	if (exec->tok_lst->output_fd == 1 && i != exec->nb_command - 1)
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
	close_fd(exec->pipe_fd[0], exec->pipe_fd[1]);
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