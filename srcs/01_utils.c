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

void	error_exit(t_mal_lst *mal_lst)
{
	printf("Malloc error\n");
	free_lst_malloc(mal_lst);
	exit (1);
}

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

char **lst_to_str_array(t_array_lst *lst, t_mal_lst **mal_lst)
{
	char 		**result;
	t_array_lst *head;
	int 		i;

	i = 0;
	head = lst;
	while (lst)
	{
		i++;
		lst = lst->next;
	}
	result = malloc((i + 1) * sizeof(char *));
	if (!result)
		error_exit(*mal_lst);
	lstadd_back_malloc(mal_lst, lstnew_malloc(result));
	i = 0;
	while (head)
	{
		result[i] = head->content;
		i++;
		head = head->next;
	}
	result[i] = 0;
	return (result);
}