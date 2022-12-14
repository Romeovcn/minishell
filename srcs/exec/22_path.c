/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   22_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:07:33 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/14 19:20:12 by jsauvage         ###   ########.fr       */
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
		free_exit(exec, 127);
	res = ft_abs_path(cmd->content, exec);
	if (res)
		return (res);
	if (!path)
		free_exit(exec, 127);
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

char	*get_path_envp(t_exec *exec)
{
	t_env_lst	*tmp;
	
	tmp = exec->env_lst;
	while (tmp)
	{
		if (tmp->name[0] == 'P' && tmp->name[1] == 'A' && tmp->name[2] == 'T' 
			&& tmp->name[3] == 'H' && tmp->name[4] == '\0')
			break ;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		free_exit(exec, 127);
	return(tmp->value);
}
