#include "minishell.h"

t_mal_lst	*lstnew_malloc(void *adr)
{
	t_mal_lst	*result;

	result = malloc(sizeof(t_mal_lst));
	if (!result)
		return (0);
	result->adr = adr;
	result->next = NULL;
	return (result);
}

t_mal_lst	*lstlast_malloc(t_mal_lst *lst)
{
	t_mal_lst	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstadd_back_malloc(t_mal_lst **lst, t_mal_lst *new)
{
	t_mal_lst	*last;

	if (*lst)
	{
		last = lstlast_malloc(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void free_lst_malloc(t_mal_lst *lst)
{
	t_mal_lst *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->adr);
		free(lst);
		lst = tmp;
	}
}