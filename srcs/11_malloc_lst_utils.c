#include "minishell.h"

t_malloc_list	*ft_lstnew_malloc(void *adr)
{
	t_malloc_list	*result;

	result = malloc(sizeof(t_malloc_list));
	if (!result)
		return (0);
	result->adr = adr;
	result->next = NULL;
	return (result);
}

t_malloc_list	*ft_lstlast_malloc(t_malloc_list *lst)
{
	t_malloc_list	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_lstadd_back_malloc(t_malloc_list **lst, t_malloc_list *new)
{
	t_malloc_list	*last;

	if (*lst)
	{
		last = ft_lstlast_malloc(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void free_lst_malloc(t_malloc_list *lst)
{
	t_malloc_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->adr);
		free(lst);
		lst = tmp;
	}
}