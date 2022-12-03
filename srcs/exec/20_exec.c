/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:14:18 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/03 15:09:52 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipex_exec(t_exec *exec)
{
	t_exec	*tmp;
	int		i;

	tmp = exec;
	i = 0;
	while (i < tmp->nb_command)
	{
		if (pipe(tmp->fd) == -1)
			return ;
		exec->pid[i] = fork();
		if (exec->pid[i] == 0)
			exec_token(tmp, i);
		if (tmp->tok_lst->next && tmp->tok_lst->next->input_fd == 0)
			dup2(tmp->fd[0], STDIN_FILENO);
		close_fd(tmp->fd[0], tmp->fd[1]);
		i++;
		tmp->tok_lst = tmp->tok_lst->next;
	}
}

void	init_exec(t_exec *exc, t_tok_lst *t_lst, t_mal_lst **m_lst, char **env)
{
	exc->tok_lst = t_lst;
	exc->mal_lst = *m_lst;
	exc->nb_command = ft_lstsize_token(t_lst);
	exc->pid = malloc(exc->nb_command * sizeof(pid_t));
	if (!exc->pid)
		return ;
	lstadd_back_malloc(m_lst, lstnew_malloc(exc->pid));
	exc->envp = env;
	exc->here_doc_lst = NULL;
}

int	exec(t_tok_lst *tok_lst, char **envp, t_mal_lst **mal_lst)
{
	t_tok_lst	*head_tok_lst;
	int			stdin_fd;
	int			status;
	t_exec		exec;

	stdin_fd = dup(0);
	init_exec(&exec, tok_lst, mal_lst, envp);
	head_tok_lst = exec.tok_lst;
	if (check_heredoc(&exec) == 1)
		here_doc_manage(&exec);
	if (exec.nb_command > 0)
		pipex_exec(&exec);
	status = error_manager(&exec, head_tok_lst);
	heredoc_rm(tok_lst);
	dup2(stdin_fd, 0);
	return (status);
}
