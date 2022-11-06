#include "minishell.h"

t_token_list	*ft_lstnew_token()
{
	t_token_list	*result;

	result = malloc(sizeof(t_token_list));
	if (!result)
		return (0);
	result->command = NULL;
	result->flags = NULL;
	result->args = NULL;
	result->input = 0;
	result->in_file = NULL;
	result->delimiter = NULL;
	result->output = 1;
	result->out_file = NULL;
	result->next = NULL;
	return (result);
}

t_token_list	*ft_lstlast_token(t_token_list *lst)
{
	t_token_list	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_lstadd_back_token(t_token_list **lst, t_token_list *new)
{
	t_token_list	*last;

	if (*lst)
	{
		last = ft_lstlast_token(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void ft_read_lst_token(t_token_list *lst)
{
	int i = 0;

	while (lst)
	{
		printf("index=%d %d\n", i, lst->output);
		lst = lst->next;
	}
}

void free_lst_token(t_token_list *lst)
{
	t_token_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}