/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:08:17 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 14:56:12 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_close_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

void	ft_dup(t_pipex *pipex, int i)
{
	if (i == 0)
	{
		if (pipex->here_doc_bool == 0)
			dup2(pipex->fd_infile, STDIN_FILENO);
		else
			dup2(pipex->here_doc_fd, STDIN_FILENO);
		dup2(pipex->fd[1], STDOUT_FILENO);
	}
	else if (i == pipex->nb_cmd - 1)
		dup2(pipex->fd_outfile, STDOUT_FILENO);
	else
		dup2(pipex->fd[1], STDOUT_FILENO);
}

void	ft_check_file(t_pipex *pipex, int i)
{
	if (i == 0 && access(pipex->infile, F_OK) == 0
		&& access(pipex->infile, R_OK) != 0)
	{
		ft_close_fd(pipex->fd[0], pipex->fd[1]);
		ft_free(pipex, pipex->cpy_head_cmd);
		exit(1);
	}
	else if (i == pipex->nb_cmd - 1 && access(pipex->outfile, F_OK) == 0
		&& access(pipex->outfile, R_OK) != 0)
	{
		ft_close_fd(pipex->fd[0], pipex->fd[1]);
		ft_free(pipex, pipex->cpy_head_cmd);
		exit(1);
	}
	else if (i == 0 && access(pipex->infile, F_OK) == -1)
	{
		ft_close_fd(pipex->fd[0], pipex->fd[1]);
		ft_free(pipex, pipex->cpy_head_cmd);
		exit(126);
	}
}
