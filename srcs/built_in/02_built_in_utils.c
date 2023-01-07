#include "minishell.h"

int exec_built_in(t_exec *exec, int is_fork)
{
	char **args;
	int return_value;

	return_value = 0;
	args = lst_to_str_array(exec->tok_lst->args, exec);
	if (ft_strmatch(args[0], "exit"))
		return_value = ft_exit(args, exec);
	else if (ft_strmatch(args[0], "export"))
		return_value = export_env(exec, &exec->mal_lst, args);
	else if (ft_strmatch(args[0], "unset"))
		return_value = unset_env(&exec->env_lst, args);
	else if (ft_strmatch(args[0], "env"))
		return_value = ft_env(args, exec->env_lst);
	else if (ft_strmatch(args[0], "cd"))
		return_value = ft_cd(args, &exec->env_lst);
	else if (ft_strmatch(args[0], "pwd"))
		return_value = ft_pwd(exec->env_lst);
	else if (ft_strmatch(args[0], "echo"))
		return_value = ft_echo(args, *exec);
	if (is_fork)
	{
		close(exec->pipe_fd[0]);
		close(exec->pipe_fd[1]);
		close(exec->stdin_fd);
		free_lst_malloc(exec->mal_lst);
		free_env_lst(exec->env_lst);
	}
	return (return_value);
}

int	is_built_in(char *command)
{
	if (ft_strmatch(command, "exit"))
		return (1);
	if (ft_strmatch(command, "export"))
		return (1);
	if (ft_strmatch(command, "unset"))
		return (1);
	if (ft_strmatch(command, "env"))
		return (1);
	if (ft_strmatch(command, "cd"))
		return (1);
	if (ft_strmatch(command, "pwd"))
		return (1);
	if (ft_strmatch(command, "echo"))
		return (1);
	return (0);
}

int	is_built_in_no_fork(char *command) // execute not in fork if no pipe
{
	if (ft_strmatch(command, "exit"))
		return (1);
	if (ft_strmatch(command, "export"))
		return (1);
	if (ft_strmatch(command, "unset"))
		return (1);
	if (ft_strmatch(command, "cd"))
		return (1);
	return (0);
}

int	check_exit_error(int i, char **args, t_exec *exec)
{
	if (i == 1)
		return (0);
	if (i > 2)
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	i = 0;
	while (args[1][i])
	{
		if (i == 0 && args[1][i] == '-')
			i++;
		if (!ft_isdigit(args[1][i]) || i > 18)
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			free_env_lst(exec->env_lst);
			free_lst_malloc(exec->mal_lst);
			exit(2);
		}
		i++;
	}
	return (0);
}