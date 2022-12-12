#include "minishell.h"

int exec_built_in(t_tok_lst *tok_lst, int status, t_mal_lst **mal_lst, t_env_lst **env_lst)
{
	char **args;

	// printf("THIS IS BUILTIN\n");
	args = lst_to_str_array(tok_lst->args, mal_lst);
	if (ft_strmatch(args[0], "exit"))
		return (ft_exit(args, status, *mal_lst, *env_lst));
	else if (ft_strmatch(args[0], "export"))
		return (export_env(env_lst, mal_lst, args));
	else if (ft_strmatch(args[0], "unset"))
		return (unset_env(env_lst, args));
	else if (ft_strmatch(args[0], "env"))
		return (ft_env(args, *env_lst));
	else if (ft_strmatch(args[0], "cd"))
		return (ft_cd(args, *env_lst));
	else if (ft_strmatch(args[0], "pwd"))
		return (ft_pwd(*env_lst));
	else if (ft_strmatch(args[0], "echo"))
		return (ft_echo(args));
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