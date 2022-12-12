/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/12 17:42:56 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(t_mal_lst *mal_lst)
{
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

void	free_array(char **arr)
{
	int	count;
	int	i;

	count = 0;
	while (arr[count])
		count++;
	i = 0;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char **envp_to_str_array(t_env_lst *lst, char **old_envp)
{
	char		**res;
	t_env_lst	*head;
	char		*tmp;
	int			i;

	if (old_envp)
		free_array(old_envp);
	head = lst;
	i = 0;
	while (head)
	{
		i++;
		head = head->next;
	}
	res = malloc((i + 1) * sizeof(char *));
	head = lst;
	i = 0;
	while (head)
	{
		tmp = ft_strjoin(head->name, "=");
		res[i] = ft_strjoin(tmp, head->value);
		free(tmp);
		i++;
		head = head->next;
	}
	res[i] = NULL;
	return (res);
}

char	*ft_strjoin_mal(char const *s1, char const *s2, t_mal_lst **mal_lst)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	lstadd_back_malloc(mal_lst, lstnew_malloc(result));
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = 0;
	return (result);
}