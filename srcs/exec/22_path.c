/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:07:33 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/16 23:04:09 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_right_path(char *path, t_array_lst *cmd, t_exec *exec)
{
	char	**split_path;
	int		i;
	char	*res;
	char	*tmp;

	if (ft_strlen(cmd->content) == 0)
		free_close_exit(exec, 127, exec->pipe_fd[0], exec->pipe_fd[1]);
	res = ft_abs_path(cmd->content, exec);
	if (res)
		return (res);
	if (!path)
		free_close_exit(exec, 127, exec->pipe_fd[0], exec->pipe_fd[1]);
	split_path = ft_split(path, ':');
	i = 0;
	while (split_path[i])
	{
		tmp = ft_strjoin(split_path[i], "/");
		res = ft_strjoin(tmp, cmd->content);
		free(tmp);
		if (access(res, X_OK) == 0)
			return (ft_strdup(res));
		free(res);
		i++;
	}
	res = NULL;
	ft_null_access(res, split_path, exec);
}
