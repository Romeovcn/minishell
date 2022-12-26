/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_buit_in_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:28:19 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/16 17:28:44 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	built_in_error(t_tok_lst *tok_lst, int stdin_fd)
{
	char	*file_error;

	file_error = get_wrong_access(tok_lst);
	if (is_directory(file_error) == 1)
		error_message(file_error, "Is a directory\n");
	else if (file_exist(file_error) == 0)
		error_message(file_error, "No such file or directory\n");
	else
		error_message(file_error, "Permission denied\n");
	close(stdin_fd);
	return ;
}

void	built_in_error_manage(t_exec *exec)
{
	if (check_outfile(exec->tok_lst, exec))
	{
		built_in_error(exec->tok_lst, exec->stdin_fd);
		return ;
	}
	if (check_infile(exec->tok_lst, exec))
	{
		built_in_error(exec->tok_lst, exec->stdin_fd);
		return ;
	}
}
