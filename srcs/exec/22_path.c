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

char	*find_right_path(char *path, t_array_lst *cmd)
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
			return (ft_strdup(res));
		free(res);
		i++;
	}
	res = NULL;
	ft_null_access(res, split_path);
}
