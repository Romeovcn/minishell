/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/09 16:25:33 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_name_match(char *env1, char *env2)
{
	int		i;
	while (env1[i] && env2[i])
	{
		if (env1[i] == '=' || env2[i] == '=')
			break ;
		if (env1[i] != env2[i])
			break ;
		i++;
	}
	if (env1[i] != '=' && env1[i] != '\0')
		return (0);
	if (env2[i] != '=' && env1[i] != '\0')
		return (0);
	return (1);
}

t_env_lst	*get_env_lst(char **env)
{
	t_env_lst	*env_lst;
	char		*content;
	int			i;

	i = 0;
	env_lst = NULL;
	while (env[i])
	{
		content = ft_strdup(env[i]);
		lstadd_back_env(&env_lst, lstnew_env(content));
		i++;
	}
	return (env_lst);
}

int	change_env_value(char *name, char *new_value, t_env_lst *env_lst)
{
	// while (env_lst)
	// {
	// 	if (ft_strmatch(env_lst->name, name))
	// 	{
	// 		free(name);
	// 		env_lst->value = new_value;
	// 		return (1);
	// 	}
	// 	env_lst = env_lst->next;
	// }
	return (0);
}

char	*get_env_value(char *name, t_env_lst *env_lst, int status)
{
	// if (ft_strmatch(name, "?"))
	// 	return (ft_itoa(status));
	// while (env_lst)
	// {
	// 	if (ft_strmatch(name, env_lst->name))
	// 		return (env_lst->value);
	// 	env_lst = env_lst->next;
	// }
	return (NULL);
}

void free_env_lst(t_env_lst *env_lst)
{
	t_env_lst *tmp;

	while (env_lst)
	{
		tmp = env_lst->next;
		free(env_lst->content);
		free(env_lst);
		env_lst = tmp;
	}
}