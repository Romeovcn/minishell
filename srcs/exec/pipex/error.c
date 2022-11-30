/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 14:01:37 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 14:55:26 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_crash_pid(int pid, int fd[2])
{
	if (pid < 0)
	{
		ft_close_fd(fd[0], fd[1]);
		return (0);
	}
	return (1);
}

static void	ft_print_error(char *message, char *error)
{
	ft_putstr_fd(message, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_exit_error(t_pipex *pipex, t_cmd *cmd, int i)
{
	char	*file;
	int		file_fd;

	if (i == 0)
		file = ft_strdup(pipex->infile);
	else if (i == pipex->nb_cmd - 1)
		file = ft_strdup(pipex->outfile);
	if (i == 0 || i == pipex->nb_cmd)
		file_fd = open(file, O_RDONLY);
	if (WEXITSTATUS(pipex->status) == 1 && (i == 0 || i == pipex->nb_cmd - 1)
		&& file_fd == -1)
		ft_print_error("permission denied", file);
	else if (WEXITSTATUS(pipex->status) == 126
		&& access(cmd->arg[0], X_OK) == -1)
		ft_print_error("permission denied", cmd->arg[0]);
	else if (WEXITSTATUS(pipex->status) == 126)
		ft_print_error("no such file or directory", file);
	else if (WEXITSTATUS(pipex->status) == 127)
		ft_print_error("command not found", cmd->arg[0]);
	if (i == 0 || i == pipex->nb_cmd - 1)
		free(file);
}
