/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:14:18 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/15 20:45:04 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipex_exec(t_exec *exec)
{
	t_tok_lst	*head;
	t_exec		*tmp;
	int			i;
	int status;

	head = exec->tok_lst;
	tmp = exec;
	i = 0;
	while (i < tmp->nb_command)
	{
		if (pipe(tmp->pipe_fd) == -1)
			return ;
		exec->pid[i] = fork();
		if (exec->pid[i] < 0)
		{
			close_fd(tmp->pipe_fd[0], tmp->pipe_fd[1]);
			free_exit(exec, 1);
		}
		if (exec->pid[i] > 0)
		{
			signal(SIGINT, handle_signal);
			signal(SIGQUIT, handle_signal);
		}
		if (exec->pid[i] == 0)
			exec_token(tmp, i);
		dup2(tmp->pipe_fd[0], STDIN_FILENO);
		close_fd(tmp->pipe_fd[0], tmp->pipe_fd[1]);
		i++;
		tmp->tok_lst = tmp->tok_lst->next;
	}
	exec->tok_lst = head;
}

void init_exec(t_exec *exec)
{
	exec->nb_command = ft_lstsize_token(exec->tok_lst);
	exec->pid = malloc(exec->nb_command * sizeof(pid_t));
	if (!exec->pid)
		return ;
	lstadd_back_malloc(&exec->mal_lst, lstnew_malloc(exec->pid));
	exec->here_doc_lst = NULL;
}

int	exec(t_exec *exec)
{
	t_tok_lst	*head_tok_lst;
	int			stdin_fd;

	stdin_fd = dup(0);
	head_tok_lst = exec->tok_lst;
	if (check_heredoc(exec) == 1)
	{
		here_doc_manage(exec);
		if (G_STATUS != 0)
		{
			heredoc_rm(exec->tok_lst);
			dup2(stdin_fd, 0);
			return (0);
		}
	}
	if (exec->nb_command == 1 && exec->tok_lst->args && is_built_in_no_fork(exec->tok_lst->args->content))
	{
		G_STATUS = exec_built_in(exec, FALSE);
		close_fd(exec->pipe_fd[0], exec->pipe_fd[1]);
		return (0);
	}
	if (exec->nb_command > 0)
		pipex_exec(exec);
	error_manager(exec, head_tok_lst);
	heredoc_rm(exec->tok_lst);
	dup2(stdin_fd, 0);
	close(stdin_fd);
}
