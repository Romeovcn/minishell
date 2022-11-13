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

void	ft_env(t_env_lst *env_lst)
{
	while (env_lst)
	{
		printf("%s=%s\n", env_lst->name, env_lst->value);
		env_lst = env_lst->next;
	}
}

void	ft_exit(t_mal_lst *mal_lst)
{
	free_lst_malloc(mal_lst);
	printf("ft_exit...\n");
	exit (0);
}

void	ft_pwd(void)
{
	char	*pwd_path;
	char	buff[PATH_MAX];

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
	if (chdir(path) < 0)
		printf("Error cd\n");
}
