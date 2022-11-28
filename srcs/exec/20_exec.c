/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:14:18 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/28 15:46:57 by jsauvage         ###   ########.fr       */
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
		if (pipe(tmp->fd) == -1)
			return ;
		exec->pid[i] = fork();
		if (exec->pid[i] == 0)
			simple_exec(tmp, i);
		if (tmp->tok_lst->next && tmp->tok_lst->next->input_fd != 0)
		{
			printf("test\n");
			dup2(tmp->fd[0], STDIN_FILENO);
		}
		close_fd(tmp->fd[0], tmp->fd[1]);
		i++;
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
	exec->here_doc_lst = NULL;
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
		here_doc_manage(exec);
	if (exec->nb_command > 1)
		pipex_exec(exec);
	i = 0;
	while (i < exec->nb_command)
	{
		waitpid(exec->pid[i], &status, 0);
		i++;
	}
	return (status);
}
