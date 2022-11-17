/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/13 03:15:11 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_env(char *str)
{
	int	i;

	i = 0;
	if (str[i] != '$' || !str[i + 1])
		return (0);
	if (str[i + 1] != '\'' && str[i + 1] != '\"')
		return (1);
	return (0);
}

char	*parse_env_name(char *str)
{
	int		i;
	char	*env_name;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) || str[i] == '\'' || str[i] == '\"')
			break ;
		i++;
	}
	env_name = malloc((i + 1) * sizeof(char));
	if (!env_name)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (isspace(*str) || *str == '\'' || *str == '\"')
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
	while (**str)
	{
		if (ft_isspace(**str) || **str == '\'' || **str == '\"')
			break ;
		(*str)++;
	}
}
