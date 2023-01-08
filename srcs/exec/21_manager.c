/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_manager.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:46:29 by jsauvage          #+#    #+#             */
/*   Updated: 2023/01/05 18:33:31 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(t_exec *exec, int i)
{
	char	**args;
	char	*path;

	args = lst_to_str_array(exec->tok_lst->args, exec);
	if (!is_built_in(args[0]))
		path = get_right_path(get_env_value("PATH", exec),
				exec->tok_lst->args, exec);
	if (is_built_in(args[0]))
		free_exit(exec, exec_built_in(exec), TRUE);
	close_fds(2, exec->pipe_fd[0], exec->pipe_fd[1]);
	execve(path, args, exec->envp);
}

void	exec_token(t_exec *exec, int i)
{
	int	output_fd;
	int	input_fd;

	output_fd = exec->tok_lst->output_fd;
	input_fd = exec->tok_lst->input_fd;
	if (check_infile(exec->tok_lst, exec) || check_outfile(exec->tok_lst, exec))
		free_exit(exec, g_status, TRUE);
	if (i != exec->nb_command - 1)
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
	if (output_fd == REDIR_OUT)
		redir_out(exec->tok_lst);
	else if (output_fd == APP_OUT)
		append(exec->tok_lst);
	if (input_fd == REDIR_IN)
		redir_in(exec->tok_lst);
	else if (input_fd == HERE_DOC)
		here_doc(exec->tok_lst);
	if (exec->tok_lst->args != NULL)
		command(exec, i);
	free_exit(exec, 0, TRUE);
}
