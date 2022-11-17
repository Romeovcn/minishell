/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:14:55 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 16:55:45 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_exec(t_pipex *pipex, char **envp, int i)
{
	if ((i == 0 && pipex->here_doc_bool == 0) || i == pipex->nb_cmd - 1)
		ft_check_file(pipex, i);
	ft_check_access(pipex);
	ft_dup(pipex, i);
	ft_close_fd(pipex->fd[0], pipex->fd[1]);
	execve(pipex->access, pipex->cmd->arg, envp);
}

static int	ft_fork_child(t_pipex *pipex, char **envp, int i)
{
	pipex->pid[i] = fork();
	if (ft_crash_pid(pipex->pid[i], pipex->fd) == 0)
		return (0);
	if (pipex->pid[i] == 0)
		ft_exec(pipex, envp, i);
	return (1);
}

static void	ft_waitpid(t_pipex *pipex, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (i < pipex->nb_cmd)
	{
		waitpid(pipex->pid[i], &pipex->status, 0);
		ft_exit_error(pipex, cmd, i);
		cmd = cmd->next;
		i++;
	}
}

int	ft_fork_parent(t_pipex *pipex, char **envp)
{
	int	i;

	i = 0;
	while (i < pipex->nb_cmd)
	{
		if (pipe(pipex->fd) == -1)
			return (0);
		if (ft_fork_child(pipex, envp, i) == 0)
			return (0);
		dup2(pipex->fd[0], STDIN_FILENO);
		ft_close_fd(pipex->fd[0], pipex->fd[1]);
		i++;
		pipex->cmd = pipex->cmd->next;
	}
	return (1);
}

int	pipex(int ac, char **av, char **envp)
{
	t_pipex	*pipex;
	int		status;
	t_cmd	*tmp;
	t_cmd	*tmp1;

	if (ac < 5)
		return (1);
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (1);
	ft_init(av, ac - 1, pipex);
	ft_parsing(envp, av, pipex, ac);
	if (ft_pid_init(pipex) == 0)
		return (1);
	tmp = pipex->cmd;
	tmp1 = pipex->cmd;
	if (ft_check_here_doc(av, envp, pipex) == 0)
		return (1);
	ft_close_fd(pipex->fd[0], pipex->fd[1]);
	ft_waitpid(pipex, tmp);
	if (pipex->here_doc_bool == 1)
		unlink(".here_doc");
	status = WEXITSTATUS(pipex->status);
	ft_free(pipex, tmp1);
	return (status);
}
