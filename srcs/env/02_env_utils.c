/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/14 15:41:50 by jsauvage         ###   ########.fr       */
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
	if (env[i - 1] == '+')
		i--;
	name = malloc((i + 1) * sizeof(char));
	if (!name)
		exit(1);
	i = 0;
	while (env[i])
	{
		if (env[i] == '=' || (env[i] == '+' && env[i + 1] == '='))
			break ;
		name[i] = env[i];
		i++;
	}
	name[i] = 0;
	if (ft_strlen(name) == 0)
	{
		free(name);
		return (NULL);
	}
	return (name);
}

t_env_lst	*get_env_lst(char **env)
{
	t_env_lst	*env_lst;
	char		*value;
	char		*name;
	int			i;

	i = 0;
	env_lst = NULL;
	while (env[i])
	{
		name = get_env_name(env[i]);
		value = ft_strdup(getenv(name));
		lstadd_back_env(&env_lst, lstnew_env(name, value));
		i++;
	}
	return (env_lst);
}

int	change_env_value(char *name, char *new_value, t_env_lst *env_lst)
{
	while (env_lst)
	{
		if (ft_strmatch(env_lst->name, name))
		{
			free(name);
			free(env_lst->value);
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
	return ("");
}

void free_env_lst(t_env_lst *env_lst)
{
	t_env_lst *tmp;

	while (env_lst)
	{
		tmp = env_lst->next;
		free(env_lst->name);
		free(env_lst->value);
		free(env_lst);
		env_lst = tmp;
	}
}