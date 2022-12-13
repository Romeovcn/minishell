/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/13 15:20:05 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_env_lst *env_lst)
{
	if (args[1])
	{
		ft_putstr_fd("env: too many arguments\n", 2);
		return (300);
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
		free_array(exec->envp);
		free_env_lst(exec->env_lst);
		free_lst_malloc(exec->mal_lst);
		ft_putstr_fd("exit\n", 2);
		exit(WEXITSTATUS(G_STATUS));
	}
	i = 0;
	while (args[1][i])
	{
		if (i == 0 && args[1][i] == '-')
			i++;
		if (!ft_isdigit(args[1][i]) || i > 18)
		{
			printf("exit: %s: numeric argument required\n", args[1]);
			free_array(exec->envp);
			free_env_lst(exec->env_lst);
			free_lst_malloc(exec->mal_lst);
			exit(2);
		}
		i++;
	}
	exit_status = ft_atoi(args[1]) % 256;
	free_array(exec->envp);
	free_env_lst(exec->env_lst);
	free_lst_malloc(exec->mal_lst);
	exit(exit_status);
	return (0);
}

int	ft_pwd(t_env_lst *env_lst)
{
	char	*pwd_path;
	char	buff[PATH_MAX];

	pwd_path = get_env_value("PWD", env_lst);
	if (pwd_path)
		printf("%s\n", pwd_path);
	else
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
	if (cmd[i] && !ft_strncmp(cmd[i], "-n", 2))
	{
		j = 1;
		while (cmd[i][j] == 'n')
			j++;;
		if (!cmd[i][j])
		{
			nl = 0;
			i++;
		}
	}
	if (cmd[i])
		printf("%s", cmd[i++]);
	while (cmd[i])
		printf(" %s", cmd[i++]);
	if (nl == 1)
		printf("\n");
	return (0);
}

int	ft_cd(char **path, t_env_lst *env_lst)
{
	char	buff[PATH_MAX];
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_strdup(getcwd(buff, PATH_MAX));
	if (!path[1])
	{
		if (chdir(get_env_value("HOME", env_lst)) < 0)
			return (free(old_pwd), perror("cd"), 300);
	}
	else if (!path[2])
	{
		if (chdir(path[1]) < 0)
			return (free(old_pwd), perror("cd"), 300);
	}
	else
		return (free(old_pwd), ft_putstr_fd("cd: too many arguments\n", 2), 300);
	new_pwd = ft_strdup(getcwd(buff, PATH_MAX));
	change_env_value(ft_strdup("OLDPWD"), old_pwd, env_lst);
	change_env_value(ft_strdup("PWD"), new_pwd, env_lst);
	return (0);
}
