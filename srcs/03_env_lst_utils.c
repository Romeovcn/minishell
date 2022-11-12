#include "minishell.h"

t_env_lst	*lstnew_env(char *name, char *value, t_mal_lst **mal_lst)
{
	t_env_lst	*result;

	result = malloc(sizeof(t_env_lst));
	if (!result)
		return (0);
	lstadd_back_malloc(mal_lst, lstnew_malloc(result));
	result->name = name;
	result->value = value;
	result->next = NULL;
	return (result);
}

t_env_lst	*lstlast_env(t_env_lst *lst)
{
	t_env_lst	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstadd_back_env(t_env_lst **lst, t_env_lst *new)
{
	t_env_lst	*last;

	if (*lst)
	{
		last = lstlast_env(*lst);
		last->next = new;
	}
	else
		*lst = new;
}