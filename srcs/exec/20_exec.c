/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:14:18 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/29 15:41:21 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_exec(t_exec *exec)
{
	t_exec	*tmp;
	int i;

	tmp = exec;
	i = 0;
	while (i < tmp->nb_command)
	{
		if (pipe(tmp->pipe_fd) == -1)
			return ;
		exec->pid[i] = fork();
		if (exec->pid[i] == 0)
			exec_token(tmp, i);
		if (tmp->tok_lst->next && tmp->tok_lst->next->input_fd == 0) // useless i think
		dup2(tmp->pipe_fd[0], STDIN_FILENO);
		close_fd(tmp->pipe_fd[0], tmp->pipe_fd[1]);
		i++;
		tmp->tok_lst = tmp->tok_lst->next;
	}
}

t_exec	init_exec(t_tok_lst *tok_lst, t_mal_lst **mal_lst, t_env_lst **env_lst, char **envp)
{
	t_exec exec;

	exec.tok_lst = tok_lst;
	exec.mal_lst = mal_lst;
	exec.env_lst = env_lst;
	exec.nb_command = ft_lstsize_token(tok_lst);
	exec.pid = malloc(exec.nb_command * sizeof(pid_t));
	if (!exec.pid)
		return (exec);
	lstadd_back_malloc(mal_lst, lstnew_malloc(exec.pid));
	exec.envp = envp;
	exec.here_doc_lst = NULL;
	return (exec);
}

int	exec(t_tok_lst *tok_lst, char **envp, t_mal_lst **mal_lst, t_env_lst **env_lst)
{
	int 	stdin_fd;
	int		status;
	t_exec	exec;
	t_tok_lst	*head_tok_lst;

	stdin_fd = dup(0);
	status = 0;
	exec = init_exec(tok_lst, mal_lst, env_lst, envp);
	head_tok_lst = exec.tok_lst;
	if (exec.nb_command == 1 && is_built_in_no_fork(tok_lst->args->content))
	{
		exec_built_in(tok_lst, status, mal_lst, env_lst);
		return 0;
	}
	if (check_heredoc(&exec) == 1)
		here_doc_manage(&exec);
	if (exec.nb_command > 0)
		pipex_exec(&exec);
	status = error_manager(&exec, head_tok_lst);
	heredoc_rm(tok_lst);
	dup2(stdin_fd, 0);
	return (status);
}
