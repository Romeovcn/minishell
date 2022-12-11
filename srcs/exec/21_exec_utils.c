/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:14:32 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/11 18:39:12 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_newstrjoin(char *s1, char *s2)
{
	char	*newstr;

	newstr = ft_strjoin(s1, s2);
	free(s1);
	return (newstr);
}

void	close_fd(int fd1, int fd2)
{
	close(fd1);
	close(fd2);
}

int	file_exist(char *file_name)
{
	if (!file_name)
		return (0);
	if (access(file_name, F_OK) == 0)
		return (1);
	return (0);
}

int	file_exec(char *file_name)
{
	if (!file_name)
		return (0);
	if (access(file_name, X_OK) == 0)
		return (1);
	return (0);
}

int	is_directory(char *path)
{
	struct stat statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}
