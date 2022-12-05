/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:55:41 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/03 20:26:44 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_wrong_access(t_tok_lst *tok_lst)
{
	t_array_lst	*tmp;
	int			file_fd;

	tmp = tok_lst->in_file;
	while (tmp)
	{
		file_fd = open(tmp->content, O_RDONLY);
		if (file_fd == -1)
			return (tmp->content);
		tmp = tmp->next;
	}
	tmp = tok_lst->out_file;
	while (tmp)
	{
		file_fd = open(tmp->content, O_RDONLY);
		if (file_fd == -1)
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	check_outfile(t_tok_lst *tok_lst)
{
	int			file_fd;
	t_array_lst	*tmp;

	tmp = tok_lst->out_file;
	while (tmp)
	{
		file_fd = open(tmp->content, O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (file_fd == -1)
			exit(1);
		tmp = tmp->next;
	}
}

void	check_infile(t_tok_lst *tok_lst)
{
	int			file_fd;
	t_array_lst	*tmp;

	tmp = tok_lst->in_file;
	while (tmp)
	{
		file_fd = open(tmp->content, O_RDONLY);
		if (file_fd == -1)
			exit(1);
		tmp = tmp->next;
	}
}

void	ft_null_access(char *path, char **split_path)
{
	if (path == NULL)
	{
		free(split_path);
		exit(127);
	}
}

char	*ft_abs_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		if (access(cmd, X_OK) == -1)
			exit(126);
	}
	else if ((cmd[0] == '/' || cmd[0] == '.') && access(cmd, F_OK) == -1)
		exit(126);
	return (NULL);
}