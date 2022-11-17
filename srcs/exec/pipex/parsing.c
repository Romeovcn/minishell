/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 12:29:13 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 14:55:50 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_path_parsing(char **envp, t_pipex *pipex)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
				&& envp[i][3] == 'H' && envp[i][4] == '=')
		{
			pipex->path = ft_strdup(ft_strchr(envp[i], '/'));
			break ;
		}
		i++;
	}
	if (pipex->path == NULL)
	{
		free(pipex->infile);
		free(pipex->outfile);
		free(pipex);
		exit(0);
	}
}

static void	ft_cmd_parsing(char **av, int ac, t_pipex *pipex)
{
	int		i;
	t_cmd	*new;

	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		i = 3;
	else
		i = 2;
	while (i < ac - 1)
	{
		new = ft_lstnew_cmd(av[i]);
		new->arg = ft_split(new->cmd, ' ');
		ft_lstadd_back_cmd(&pipex->cmd, new);
		i++;
	}
	pipex->nb_cmd = ft_lstsize_cmd(pipex->cmd);
}

void	ft_parsing(char **envp, char **av, t_pipex *pipex, int ac)
{
	ft_path_parsing(envp, pipex);
	ft_cmd_parsing(av, ac, pipex);
}
