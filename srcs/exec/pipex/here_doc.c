/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 16:53:53 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 14:55:35 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_here_doc(char **av, char **envp, t_pipex *pipex)
{
	char	*line;
	int		len;

	pipex->here_doc_fd = open(".here_doc", O_CREAT | O_RDWR, 0666);
	line = get_next_line(0);
	len = (int)ft_strlen(line) - 1;
	if (len < (int)ft_strlen(av[2]))
		len = (int)ft_strlen(av[2]);
	while (ft_strncmp(av[2], line, len) != 0)
	{
		ft_putstr_fd(line, pipex->here_doc_fd);
		free(line);
		line = get_next_line(0);
		len = (int)ft_strlen(line) - 1;
		if (len < (int)ft_strlen(av[2]))
			len = (int)ft_strlen(av[2]);
	}
	free(line);
	close (pipex->here_doc_fd);
	pipex->here_doc_fd = open(".here_doc", O_RDWR, 0666);
	ft_fork_parent(pipex, envp);
	return (1);
}

int	ft_check_here_doc(char **av, char **envp, t_pipex *pipex)
{
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		pipex->here_doc_bool = 1;
		ft_here_doc(av, envp, pipex);
	}
	else
		if (ft_fork_parent(pipex, envp) == 0)
			return (0);
	return (1);
}
