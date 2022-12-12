#include "minishell.h"

int exec_built_in(t_exec exec, t_tok_lst *tok_lst, t_mal_lst **mal_lst, t_env_lst **env_lst) //clean arguments
{
	char **args;
	int return_value;

	return_value = 0;
	// printf("THIS IS BUILTIN\n");
	args = lst_to_str_array(tok_lst->args, mal_lst);
	if (ft_strmatch(args[0], "exit"))
		return_value = ft_exit(args, *mal_lst, *env_lst);
	else if (ft_strmatch(args[0], "export"))
		return_value = export_env(env_lst, mal_lst, args);
	else if (ft_strmatch(args[0], "unset"))
		return_value = unset_env(env_lst, args);
	else if (ft_strmatch(args[0], "env"))
		return_value = ft_env(args, *env_lst);
	else if (ft_strmatch(args[0], "cd"))
		return_value = ft_cd(args, *env_lst);
	else if (ft_strmatch(args[0], "pwd"))
		return_value = ft_pwd(*env_lst);
	else if (ft_strmatch(args[0], "echo"))
		return_value = ft_echo(args, exec);
	free_lst_malloc(exec.mal_lst);
	free_env_lst(exec.env_lst);
	free_array(exec.envp);
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