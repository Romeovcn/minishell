/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   27_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:55:41 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/14 19:26:22 by jsauvage         ###   ########.fr       */
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
		close(file_fd);
		tmp = tmp->next;
	}
	tmp = tok_lst->out_file;
	while (tmp)
	{
		if (is_directory(tmp->content) == 1)
			return (tmp->content);
		file_fd = open(tmp->content, O_RDONLY);
		if (file_fd == -1)
			return (tmp->content);
		close(file_fd);
		tmp = tmp->next;
	}
	return (NULL);
}

void	check_outfile(t_tok_lst *tok_lst, t_exec *exec)
{
	int			file_fd;
	t_array_lst	*tmp;

	tmp = tok_lst->out_file;
	while (tmp)
	{
		if (is_directory(tmp->content) == 1)
			free_exit(exec, 126);
		if (ft_strmatch(tmp->content2, "O_TRUNC"))
			file_fd = open(tmp->content, O_RDWR | O_CREAT | O_TRUNC, 0666);
		else if (ft_strmatch(tmp->content2, "O_APPEND"))
			file_fd = open(tmp->content, O_RDWR | O_CREAT | O_APPEND, 0666);
		if (file_fd == -1)
			free_exit(exec, 1);
		close(file_fd);
		tmp = tmp->next;
	}
}

void	check_infile(t_tok_lst *tok_lst, t_exec *exec)
{
	int			file_fd;
	t_array_lst	*tmp;

	tmp = tok_lst->in_file;
	while (tmp)
	{
		file_fd = open(tmp->content, O_RDONLY);
		if (file_fd == -1)
			free_exit(exec, 1);
		close(file_fd);
		tmp = tmp->next;
	}
}

void	ft_null_access(char *path, char **split_path, t_exec *exec)
{
	if (path == NULL)
	{
		free_array(split_path);
		free_exit(exec, 127);
	}
}

char	*ft_abs_path(char *cmd, t_exec *exec)
{
	if ((cmd[0] == '/' || cmd[0] == '.') && access(cmd, F_OK) == 0)
	{
		if (is_directory(cmd) == 1)
			free_exit(exec, 126);
		if (access(cmd, X_OK) == 0)
			return (cmd);
		if (access(cmd, X_OK) == -1)
			free_exit(exec, 126);
	}
	else if ((cmd[0] == '/' || cmd[0] == '.') && access(cmd, F_OK) == -1)
		free_exit(exec, 127);
	return (NULL);
}
