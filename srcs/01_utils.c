/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent  <rvincent@student.42.fr   >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/09 17:40:01 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_char(char const *s1, char c, t_mal_lst **mal_lst)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc((ft_strlen(s1) + 1 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	lstadd_back_malloc(mal_lst, lstnew_malloc(result));
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	result[j++] = c;
	result[j] = 0;
	return (result);
}
