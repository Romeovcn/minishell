/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:52:56 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 14:55:31 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_newstrjoin(char *s1, char *s2)
{
	char	*newstr;

	newstr = ft_strjoin(s1, s2);
	free(s1);
	return (newstr);
}

void	ft_free_split(char **arr)
{
	int	count;
	int	i;

	count = 0;
	while (arr[count])
		count++;
	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_linked_list(t_cmd **list)
{
	t_cmd	*tmp;

	tmp = *list;
	while (*list)
	{
		tmp = (*list)->next;
		ft_free_split((*list)->arg);
		free(*list);
		*list = tmp;
	}
	*list = NULL;
}

void	ft_free(t_pipex *pipex, t_cmd *cmd)
{
	free(pipex->infile);
	free(pipex->outfile);
	free(pipex->pid);
	free(pipex->path);
	ft_free_linked_list(&cmd);
	free(pipex);
}
