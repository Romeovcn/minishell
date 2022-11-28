/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/13 03:14:42 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **args, t_env_lst *env_lst)
{
	if (args[1])
	{
		printf("env: too many arguments\n");
		return ;
	}
	while (env_lst)
	{
		printf("%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
}

void	ft_exit(char **args, int status, t_mal_lst *mal_lst, t_env_lst *env_lst)
{
	int i;

	i = 0;
	while (args[i])
		i++;
	if (i > 2)
		return (void)printf("exit: too many arguments\n");
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
	free_env_lst(env_lst);
	free_lst_malloc(mal_lst);
	printf("exit\n");
	exit(ft_atoi(args[1]) % 256);
}

void	ft_pwd(char **args)
{
	char	*pwd_path;
	char	buff[PATH_MAX];

	if (args[1])
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	pwd_path = getenv("PWD");
	if (pwd_path)
		printf("%s\n", pwd_path);
	else
		printf("%s\n", getcwd(buff, PATH_MAX));
}

void	ft_echo(char **cmd)
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
}

void	ft_cd(char *path)
{
	if (chdir("Makefile") < 0)
		perror("cd");
	else
	{
		// change OLD_PWD && PWD
		// export_env();
	}
}
