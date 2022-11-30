#include "minishell.h"

void	error_message_127(char *command)
{
	ft_putstr_fd("Command '", 2);
	ft_putstr_fd(command, 2);
	ft_putstr_fd("' not found\n", 2);
}

void    error_status(t_tok_lst *tok_lst, int status)
{
	// if (WEXITSTATUS(status) == 1) {}
	// if (WEXITSTATUS(status) == 126) {}
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
