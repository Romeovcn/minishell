#include "minishell.h"

void	error_message_127(char *command)
{
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("' not found\n", 2);
}

void	error_message(char *file, char *message)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
}

char	*check_access(t_tok_lst *tok_lst)
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

void    error_status(t_tok_lst *tok_lst, int status)
{
	char	*file_error;

	file_error = check_access(tok_lst);
	if (status == 1 && file_exist(file_error) == 0)
		error_message(file_error, "No such file or directory\n");
	if (status == 1 && file_exec(file_error) == 0)
		error_message(file_error, "Permission denied\n");
	if (status == 126)
		error_message(tok_lst->args->content, "Permission denied\n");
	if (status == 127)
		error_message_127(tok_lst->args->content);
}

int	error_manager(t_exec *exec, t_tok_lst *tok_lst)
{
	int			status;
	int			i;

	i = 0;
	printf("arg: %s\n", tok_lst->args->content);
	while (i < exec->nb_command)
	{
		waitpid(exec->pid[i++], &status, 0);
		printf("status: %d\n", WEXITSTATUS(status));
		error_status(tok_lst, WEXITSTATUS(status));
		tok_lst = tok_lst->next;
	}
	return (status);
}
