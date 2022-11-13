/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/13 03:13:14 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_env(t_env_lst **env_lst, t_mal_lst **mal_lst, char **options)
{
	char	*value_found;
	char	*name;
	int		i;

	i = 1;
	while (options[i])
	{
		name = get_env_name(options[i], mal_lst);
		if (name)
		{
			while (*(options[i]))
			{
				if (*(options[i]) == '=' && *(options[i])++)
					break ;
				options[i]++;
			}
			value_found = get_env_value(name, *env_lst);
			if (value_found)
				change_env_value(name, options[i], *env_lst);
			else
				lstadd_back_env(env_lst, lstnew_env(name, options[i], mal_lst));
		}
		i++;
	}
}

void	unset_env(t_env_lst **env_lst, char **options)
{
	t_env_lst	*tmp_previous;
	t_env_lst	*env_head;
	int			i;

	i = 1;
	while (options[i])
	{
		// if (ft_strchr(options[i], '='))
		// {
		// 	printf("unset: '%s': not a valid identifier\n", options[i++]);
		// 	continue ;
		// }
		tmp_previous = NULL;
		env_head = *env_lst;
		while (env_head)
		{
			if (ft_strmatch(options[i], env_head->name))
			{
				if (!tmp_previous)
					*env_lst = (*env_lst)->next;
				else
					tmp_previous->next = env_head->next;
				break ;
			}
			tmp_previous = env_head;
			env_head = env_head->next;
		}
		i++;
	}
}
