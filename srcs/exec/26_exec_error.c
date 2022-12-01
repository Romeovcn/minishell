#include "minishell.h"

static void	error_message_127(char *command)
{
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("' not found\n", 2);
}

static void	error_message(char *file, char *message)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
}

void    error_status(t_tok_lst *tok_lst, int status)
{
	char	*file_error;

	file_error = get_wrong_access(tok_lst);
	if (status == 1 && file_exist(file_error) == 0)
		error_message(file_error, "No such file or directory\n");
	else if (status == 1 && file_exec(file_error) == 0)
		error_message(file_error, "Permission denied\n");
	else if (status == 126)
		error_message(tok_lst->args->content, "Permission denied\n");
	else if (status == 127)
		error_message_127(tok_lst->args->content);
	if (!file_error)
		free(file_error);
}

int	error_manager(t_exec *exec, t_tok_lst *tok_lst)
{
	int			status;
	int			i;

	i = 0;
	while (i < exec->nb_command)
	{
		waitpid(exec->pid[i++], &status, 0);
		printf("status: %d\n", WEXITSTATUS(status));
		error_status(tok_lst, WEXITSTATUS(status));
		tok_lst = tok_lst->next;
	}
	return (status);
}
