/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:14:18 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/16 17:38:27 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pipex_exec(t_exec *exec)
{
	t_tok_lst	*head;
	t_exec		*tmp;
	int			i;

	head = exec->tok_lst;
	tmp = exec;
	i = 0;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
		signal(SIGQUIT, sig_process);
		signal(SIGINT, sig_process);
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

void	exec(t_exec *exec)
{
	int		stdin_fd;

	stdin_fd = dup(0);
	if (check_heredoc(exec) == 1)
	{
		here_doc_manage(exec);
		if (G_STATUS == 777)
		{
			heredoc_rm(exec->tok_lst);
			dup2(stdin_fd, 0);
			close(stdin_fd);
			G_STATUS = 130;
			return ;
		}
	}
	if (exec->nb_command == 1 && exec->tok_lst->args && is_built_in_no_fork(exec->tok_lst->args->content))
	{
		built_in_error_manage(exec, stdin_fd);
		G_STATUS = exec_built_in(exec, FALSE);
		close(stdin_fd);
		return ;
	}
	if (exec->nb_command > 0)
		pipex_exec(exec);
	error_manager(*exec);
	heredoc_rm(exec->tok_lst);
	dup2(stdin_fd, 0);
	close(stdin_fd);
}
