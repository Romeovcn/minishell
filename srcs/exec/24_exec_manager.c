/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   24_exec_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:46:29 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/05 16:17:53 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(t_exec *exec, int i)
{
	char	**args;
	char	*path;

	args = lst_to_str_array(exec->tok_lst->args, exec->mal_lst);
	if (!is_built_in(args[0]))
	path = get_right_path(getenv("PATH"), exec->tok_lst->args);
	if (exec->tok_lst->output_fd == 1 && i != exec->nb_command - 1)
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
	close_fd(exec->pipe_fd[0], exec->pipe_fd[1]);
	if (is_built_in(args[0]))
		exit(exec_built_in(exec->tok_lst, 0, exec->mal_lst, exec->env_lst));
	execve(path, args, exec->envp);
	exit(0);
}

// static void	handle_pid_sigint(int num)
// {
// 	write(1, "\n", 1);
// }

void	exec_token(t_exec *exec, int i)
{
	// signal(SIGINT, handle_pid_sigint);
	if (exec->tok_lst->output_fd == REDIR_OUT
		|| exec->tok_lst->output_fd == APP_OUT)
		check_outfile(exec->tok_lst);
	if (exec->tok_lst->output_fd == REDIR_OUT)
		redir_out(exec->tok_lst);
	if (exec->tok_lst->input_fd == REDIR_IN)
	{
		check_infile(exec->tok_lst);
		redir_in(exec->tok_lst);
	}
	if (exec->tok_lst->input_fd == HERE_DOC)
		here_doc(exec->tok_lst);
	if (exec->tok_lst->output_fd == APP_OUT)
		append(exec->tok_lst);
	if (exec->tok_lst->args != NULL)
		command(exec, i);
	exit(0);
}
