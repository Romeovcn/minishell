/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:24:18 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 14:55:40 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_init(char **av, int ac, t_pipex *pipex)
{
	pipex->fd_infile = open(av[1], O_RDONLY);
	pipex->infile = ft_strdup(av[1]);
	pipex->outfile = ft_strdup(av[ac]);
	pipex->fd_outfile = open(av[ac], O_CREAT | O_TRUNC | O_RDWR, 0666);
	pipex->access = NULL;
	pipex->path = NULL;
	pipex->cmd = NULL;
	pipex->here_doc_bool = 0;
}

int	ft_pid_init(t_pipex *pipex)
{
	pipex->pid = malloc(sizeof(int) * pipex->nb_cmd);
	if (pipex->pid == NULL)
		return (0);
	pipex->cpy_head_cmd = pipex->cmd;
	return (1);
}
