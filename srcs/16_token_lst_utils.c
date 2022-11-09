#include "minishell.h"

t_tok_list	*lstnew_token(t_mal_lst **mal_lst)
{
	t_tok_list	*result;

	result = malloc(sizeof(t_tok_list));
	if (!result)
		return (0);
	lstadd_back_malloc(mal_lst, lstnew_malloc(result));
	result->options = NULL;
	result->input_fd = 0;
	result->in_file = NULL;
	result->delimiter = NULL;
	result->output_fd = 1;
	result->out_file = NULL;
	result->next = NULL;
	return (result);
}

t_tok_list	*lstlast_token(t_tok_list *lst)
{
	t_tok_list	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstadd_back_token(t_tok_list **lst, t_tok_list *new)
{
	t_tok_list	*last;

	if (*lst)
	{
		last = lstlast_token(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void read_lst_token(t_tok_list *lst)
{
	int i = 0;

	while (lst)
	{
		printf("index=%d %d\n", i, lst->output_fd);
		lst = lst->next;
	}
}

void free_lst_token(t_tok_list *lst)
{
	t_tok_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}