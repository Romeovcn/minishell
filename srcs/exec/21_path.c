/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:07:33 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 19:04:40 by jsauvage         ###   ########.fr       */
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
		{
			printf("hello\n");
			// path = ft_strdup(cmd);
			return (cmd);
		}
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
		res = ft_strjoin(split_path[i], "/");
		res = ft_strjoin(res, cmd->content);
		accss = access(res, X_OK);
		if (accss == 0)
			return (ft_strdup(res));
		free(res);
		i++;
	}
	ft_null_access(path, split_path);
}
