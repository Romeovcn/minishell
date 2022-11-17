/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 16:10:54 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 14:55:57 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_null_access(t_pipex *pipex, char **split_path)
{
	if (pipex->access == NULL)
	{
		free(split_path);
		ft_free(pipex, pipex->cpy_head_cmd);
		exit(127);
	}
}

static int	ft_abs_path(t_pipex *pipex, char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
		{
			pipex->access = ft_strdup(cmd);
			return (0);
		}
		if (access(cmd, X_OK) == -1)
		{
			ft_free(pipex, pipex->cpy_head_cmd);
			exit(126);
		}
	}
	return (1);
}

void	ft_check_access(t_pipex *pipex)
{
	char	**split_path;
	int		i;
	char	*res;
	int		accss;

	if (ft_abs_path(pipex, pipex->cmd->arg[0]) == 0)
		return ;
	split_path = ft_split(pipex->path, ':');
	i = 0;
	pipex->access = NULL;
	while (split_path[i])
	{
		res = ft_newstrjoin(split_path[i], "/");
		res = ft_newstrjoin(res, pipex->cmd->arg[0]);
		accss = access(res, X_OK);
		if (accss == 0)
			pipex->access = ft_strdup(res);
		free(res);
		i++;
	}
	ft_null_access(pipex, split_path);
}
