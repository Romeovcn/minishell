/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/15 18:41:22 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_env_name(char *env_name)
{
	int	i;

	i = 0;
	if (env_name[i] && !ft_isalpha(env_name[i]) && env_name[i] != '_')
		return (1);
	i++;
	while (env_name[i])
	{
		if (!ft_isalnum(env_name[i]) && env_name[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

char	*get_env_str_value(char *env)
{
	char	*value;
	int		i;

	i = 0;
	while (*env && *env != '=')
		env++;
	if (*env != '=')
		return (NULL);
	env++;
	while (env[i])
		i++;
	value = malloc((i + 1) * sizeof(char));
	if (!value)
		return (NULL);
	i = 0;
	while (env[i])
	{
		value[i] = env[i];
		i++;
	}
	value[i] = 0;
	return (value);
}

int	is_concatenate(char *env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (env[i] == '+' && env[i + 1] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	export_env(t_exec *exec, t_mal_lst **mal_lst, char **args)
{
	int		return_value;
	char	*env_value;
	char	*name;
	int		i;

	i = 0;
	return_value = 0;
	while (args[++i])
	{
		name = get_env_name(args[i]);
		if (!name || check_env_name(name))
		{
			ft_putstr_fd("export: '", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			free(name);
			return_value = 1;
			continue ;
		}
		env_value = get_env_str_value(args[i]);
		if (!env_value)
		{
			free(name);
			continue ;
		}
		if (is_concatenate(args[i]))
			env_value = ft_newstrjoin(get_env_value(name, exec->env_lst), env_value);
		change_env_value(name, env_value, &exec->env_lst);
	}
	return (return_value);
}

int	unset_env(t_env_lst **env_lst, char **args)
{
	t_env_lst	*tmp_previous;
	t_env_lst	*env_head;
	int			i;

	i = 1;
	while (args[i])
	{
		tmp_previous = NULL;
		env_head = *env_lst;
		while (env_head)
		{
			if (ft_strmatch(args[i], env_head->name))
			{
				if (!tmp_previous)
					*env_lst = (*env_lst)->next;
				else
					tmp_previous->next = env_head->next;
				free(env_head->name);
				free(env_head->value);
				free(env_head);
				break ;
			}
			tmp_previous = env_head;
			env_head = env_head->next;
		}
		i++;
	}
	return (0);
}
