/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2023/01/05 18:33:31 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_env_lst *env_lst)
{
	if (args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (1);
	}
	while (env_lst)
	{
		printf("%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
	return (0);
}

int	ft_exit(char **args, t_exec *exec)
{
	int exit_status;
	int i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	if (i == 1)
	{
		free_env_lst(exec->env_lst);
		free_lst_malloc(exec->mal_lst);
		ft_putstr_fd("exit\n", 2);
		exit(g_status);
	}
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
	exit_status = ft_atoi(args[1]) % 256;
	free_env_lst(exec->env_lst);
	free_lst_malloc(exec->mal_lst);
	exit(exit_status);
	return (0);
}

int	ft_pwd(t_env_lst *env_lst)
{
	char	*pwd_path;
	char	buff[PATH_MAX];

	printf("%s\n", getcwd(buff, PATH_MAX));
	return (0);
}

int	ft_echo(char **cmd, t_exec exec)
{
	int	i;
	int	nl;
	int j;

	i = 1;
	nl = 1;
	while (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;
		if (!cmd[i][j])
		{
			nl = 0;
			i++;
		}
		else
			break;
	}
	if (cmd[i])
		printf("%s", cmd[i++]);
	while (cmd[i])
		printf(" %s", cmd[i++]);
	if (nl == 1)
		printf("\n");
	return (0);
}

int	ft_cd(char **path, t_env_lst **env_lst)
{
	char	buff[PATH_MAX];
	char	*old_pwd;
	char	*new_pwd;
	int		chdir_value;

	old_pwd = ft_strdup(getcwd(buff, PATH_MAX));
	if (!path[1])
		chdir_value = chdir(get_env_value("HOME", *env_lst)) < 0;
	else if (!path[2])
	{
		if (ft_strmatch(path[1], "-"))
			chdir_value = chdir(get_env_value("OLDPWD", *env_lst));
		else
			chdir_value = chdir(path[1]);
	}
	else
		return (free(old_pwd), ft_putstr_fd("cd: too many arguments\n", 2), 1);
	if (chdir_value < 0)
		return (free(old_pwd), perror("cd"), 1);
	new_pwd = ft_strdup(getcwd(buff, PATH_MAX));
	change_env_value(ft_strdup("OLDPWD"), old_pwd, env_lst);
	change_env_value(ft_strdup("PWD"), new_pwd, env_lst);
	return (0);
}
