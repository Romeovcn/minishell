/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/29 01:03:14 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '$' || !str[i + 1])
		return (0);
	if (!ft_isalpha(str[i + 1]) && str[i + 1] != '_' && str[i + 1] != '?')
		return (0);
	return (1);
}

char	*parse_env_name(char *str)
{
	int		i;
	char	*env_name;

	i = 0;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && str[i] != '_')
			break ;
		i++;
	}
	env_name = malloc((i + 1) * sizeof(char));
	if (!env_name)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (!ft_isalpha(*str) && *str != '_')
			break ;
		env_name[i] = *str;
		i++;
		str++;
	}
	env_name[i] = 0;
	return (env_name);
}

void	go_end_env_name(char **str)
{
	if (**str == '?')
	{
		(*str)++;
		return ;
	}
	while (**str)
	{
		if (!ft_isalpha(**str) && **str != '_')
			break ;
		(*str)++;
	}
}
