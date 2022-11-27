/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:14:18 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/27 18:34:46 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fork_child(t_exec *exec)
{
	exec->pid[exec->incr] = fork();
	// if (ft_crash_pid(exec->pid[i], exec->fd) == 0)
	// 	return (0);
	if (exec->pid[exec->incr] == 0)
		simple_exec(exec);
}

void	pipex_exec(t_exec *exec)
{
	t_exec	*tmp;

	tmp = exec;
	while (tmp->incr < tmp->nb_command)
	{
		if (pipe(tmp->fd) == -1)
			return ;
		if (exec->here_doc->position_last_heredoc != -1 &&
			tmp->incr == exec->here_doc->position_last_heredoc)
			dup2(exec->here_doc->fd_last_here_doc, STDIN_FILENO);
		fork_child(tmp);
		dup2(tmp->fd[0], STDIN_FILENO);
		close_fd(tmp->fd[0], tmp->fd[1]);
		tmp->incr++;
		tmp->tok_lst = tmp->tok_lst->next;
	}
}

void	init_exec(t_exec *exec, t_tok_lst *tok_lst, t_mal_lst *mal_lst, char **envp)
{
	exec->tok_lst = tok_lst;
	exec->mal_lst = mal_lst;
	exec->nb_command = ft_lstsize_token(tok_lst);
	exec->pid = malloc(exec->nb_command * sizeof(pid_t));
	if (!exec->pid)
		return ;
	exec->envp = envp;
	exec->incr = 0;
	exec->here_doc = malloc(sizeof(t_here_doc));
	exec->here_doc->position_last_heredoc = -1;
}

int	exec(t_tok_lst *tok_lst, char **envp, t_mal_lst *mal_lst)
{
	int		i;
	int		status;
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (0);
	init_exec(exec, tok_lst, mal_lst, envp);
	if (check_heredoc(exec) == 1)
	{
		position_last_heredoc(exec);
		here_doc_manage(exec);
	}
	if (exec->nb_command == 1)
		simple_exec(exec);
	else if (exec->nb_command > 1)
		pipex_exec(exec);
	i = 0;
	while (i < exec->nb_command)
	{
		waitpid(exec->pid[i], &status, 0);
		i++;
	}
	unlink(exec->here_doc->here_doc);
	close(exec->here_doc->fd_last_here_doc);
	return (status);
}
