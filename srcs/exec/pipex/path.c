/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<<< HEAD:srcs/exec/22_path.c
/*   Created: 2022/11/17 18:07:33 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 19:04:40 by jsauvage         ###   ########.fr       */
========
/*   Created: 2022/11/13 16:10:54 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 18:08:25 by jsauvage         ###   ########.fr       */
>>>>>>>> 031f254 (finish find right access):srcs/exec/pipex/path.c
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_null_access(char *path, char **split_path)
{
	if (path == NULL)
	{
		free(split_path);
		exit(127);
	}
}

static char	*ft_abs_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		// if (access(cmd, X_OK) == -1)
		// 	exit(126);
	}
	return (NULL);
}

char	*find_right_access(char *path, t_array_lst *cmd)
{
	char	**split_path;
	int		i;
	char	*res;
	int		accss;

	res = ft_abs_path(cmd->content);
	if (res != NULL)
		return (res);
	split_path = ft_split(path, ':');
	i = 0;
	while (split_path[i])
	{
		res = ft_newstrjoin(split_path[i], "/");
		res = ft_newstrjoin(res, cmd->content);
		accss = access(res, X_OK);
		if (accss == 0)
<<<<<<<< HEAD:srcs/exec/22_path.c
			return (ft_strdup(res));
========
			pipex->path = ft_strdup(res);
>>>>>>>> 031f254 (finish find right access):srcs/exec/pipex/path.c
		free(res);
		i++;
	}
	res = NULL;
	ft_null_access(res, split_path);
}
