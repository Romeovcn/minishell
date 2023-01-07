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
		path = get_right_path(get_env_value("PATH", exec->env_lst),
				exec->tok_lst->args, exec);
	if (exec->tok_lst->output_fd == 1 && i != exec->nb_command - 1)
		dup2(exec->pipe_fd[1], STDOUT_FILENO);
	if (is_built_in(args[0]))
		exit(exec_built_in(exec, TRUE));
	close_fds(2, exec->pipe_fd[0], exec->pipe_fd[1]);
	execve(path, args, exec->envp);
	exit(0);
}

void	exec_token(t_exec *exec, int i)
{
	int	output_fd;
	int	input_fd;

	output_fd = exec->tok_lst->output_fd;
	input_fd = exec->tok_lst->input_fd;
	if (check_infile(exec->tok_lst, exec) || check_outfile(exec->tok_lst, exec))
		free_exit(exec, g_status);
	if (output_fd == REDIR_OUT)
		redir_out(exec->tok_lst);
	if (output_fd == APP_OUT)
		append(exec->tok_lst);
	if (input_fd == REDIR_IN)
		redir_in(exec->tok_lst);
	if (input_fd == HERE_DOC)
		here_doc(exec->tok_lst);
	if (exec->tok_lst->args != NULL)
		command(exec, i);
	close_fds(3, exec->pipe_fd[0], exec->pipe_fd[1], exec->stdin_fd);
	free_lst_malloc(exec->mal_lst);
	free_env_lst(exec->env_lst);
	exit(0);
}
