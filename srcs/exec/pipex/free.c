/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   21_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:14:32 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/18 16:19:05 by jsauvage         ###   ########.fr       */
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
