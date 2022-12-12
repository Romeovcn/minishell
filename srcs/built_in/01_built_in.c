/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/06 23:41:32 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **args, t_env_lst *env_lst)
{
	if (args[1])
	{
		printf("env: too many arguments\n");
		return (1);
	}
	while (env_lst)
	{
		printf("%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
	return (0);
}

int	ft_exit(char **args, int status, t_mal_lst *mal_lst, t_env_lst *env_lst)
{
	int exit_status;
	int i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (printf("exit: too many arguments\n"), 1);
	if (i == 1)
	{
		free_env_lst(env_lst);
		free_lst_malloc(mal_lst);
		printf("exit\n");
		exit(WEXITSTATUS(status));
	}
	i = 0;
	while (args[1][i])
	{
		if (i == 0 && args[1][i] == '-')
			i++;
		if (!ft_isdigit(args[1][i]) || i > 18)
		{
			free_env_lst(env_lst);
			free_lst_malloc(mal_lst);
			printf("exit: %s: numeric argument required\n", args[1]);
			exit(2);
		}
		i++;
	}
	exit_status = ft_atoi(args[1]) % 256;
	free_env_lst(env_lst);
	free_lst_malloc(mal_lst);
	exit(exit_status);
	return (0);
}

int	ft_pwd(t_env_lst *env_lst)
{
	char	*pwd_path;
	char	buff[PATH_MAX];

	pwd_path = get_env_value(ft_strdup("PWD"), env_lst);
	if (pwd_path)
		printf("%s\n", pwd_path);
	else
		printf("%s\n", getcwd(buff, PATH_MAX));
	return (0);
}

int	ft_echo(char **cmd)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (cmd[i] && ft_strmatch(cmd[i], "-n"))
	{
		nl = 0;
		i++;
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
	if (!path[1] && chdir("/") < 0)
	{
		printf("ok\n");
		return (perror("cd"), 1);
	}
	if (path[2])
		return (printf("cd: too many arguments\n"), 1);
	// else if (path[1] && chdir(path[1]) < 0)
	// 	return (perror("cd"), 1);
	// new_pwd = ft_strdup(getcwd(buff, PATH_MAX));
	// printf("PWD=%s\nOLD=%s\n", old_pwd, new_pwd);
	// change_env_value(ft_strdup("OLDPWD"), old_pwd, env_lst);
	// change_env_value(ft_strdup("PWD"), new_pwd, env_lst);
	return (0);
}
