/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/13 21:55:39 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_name(char *env)
{
	int		i;
	char	*name;

	i = 0;
	if (env[0] == '=')
		return (NULL);
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		i++;
	}
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (env[i] == '=')
			break ;
		name[i] = env[i];
		i++;
	}
	name[i] = 0;
	return (name);
}

void	get_env_lst(t_env_lst **env_lst, char **env)
{
	char	*value;
	char	*name;
	int		i;

	i = 0;
	while (env[i])
	{
		name = get_env_name(env[i]);
		value = getenv(name);
		lstadd_back_env(env_lst, lstnew_env(name, value));
		i++;
	}
}

int	change_env_value(char *name, char *new_value, t_env_lst *env_lst)
{
	while (env_lst)
	{
		if (ft_strmatch(env_lst->name, name))
		{
			free(name);
			env_lst->value = new_value;
			return (1);
		}
		env_lst = env_lst->next;
	}
	return (0);
}

char	*get_env_value(char *name, t_env_lst *env_lst)
{
	while (env_lst)
	{
		if (ft_strmatch(name, env_lst->name))
			return (env_lst->value);
		env_lst = env_lst->next;
	}
	return (NULL);
}

void free_env_lst(t_env_lst *env_lst)
{
	t_env_lst *tmp;

	while (env_lst)
	{
		tmp = env_lst->next;
		free(env_lst->name);
		free(env_lst);
		env_lst = tmp;
	}
}