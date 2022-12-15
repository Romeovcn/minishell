/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   26_exec_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:55:43 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/15 18:34:59 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	error_message_127(char *command)
{
	if (!command)
		return ;
	ft_putstr_fd(command, 2);
	ft_putstr_fd(": command not found\n", 2);
}

static void	error_message(char *file, char *message)
{
	if (!file || !message)
		return ;
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
}

static void	error_status(t_tok_lst *tok_lst)
{
	char	*file_error;

	file_error = get_wrong_access(tok_lst);
	if (G_STATUS == 1 && file_exist(file_error) == 0)
		error_message(file_error, "No such file or directory\n");
	else if (G_STATUS == 1 && file_exec(file_error) == 0)
		error_message(file_error, "Permission denied\n");
	else if (G_STATUS == 126 && is_directory(file_error) == 1)
		error_message(file_error, "Is a directory\n");
	else if (G_STATUS == 126 && file_exist(tok_lst->args->content) == 0)
		error_message(tok_lst->args->content, "No such file or directory\n");
	else if (G_STATUS == 126 && is_directory(tok_lst->args->content))
		error_message(tok_lst->args->content, "Is a directory\n");
	else if (G_STATUS == 126)
		error_message(tok_lst->args->content, "Permission denied\n");
	else if (G_STATUS == 127 && (tok_lst->args->content[0] == '/' 
		|| tok_lst->args->content[0] == '.'))
		error_message(tok_lst->args->content, "No such file or directory\n");
	else if (G_STATUS == 127)
		error_message_127(tok_lst->args->content);
	if (!file_error)
		free(file_error); // free null ?
}

void	error_manager(t_exec *exec, t_tok_lst *tok_lst)
{
	int	i;
	int status;

	i = 0;
	while (tok_lst && waitpid(exec->pid[i], &status, 0) > 0)
	{
		G_STATUS = WEXITSTATUS(status);
		if (G_STATUS == 131)
			G_STATUS = 33536; // to fix
		error_status(tok_lst);
		tok_lst = tok_lst->next;
		i++;
	}
}
