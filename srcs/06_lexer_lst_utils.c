#include "minishell.h"

t_lexed_list	*lstnew_lexer(void *content, int operator, t_malloc_list **malloc_lst)
{
	t_lexed_list	*result;

	result = malloc(sizeof(t_lexed_list));
	if (!result)
		return (0);
	result->content = content;
	result->operator = operator;
	result->next = NULL;
	ft_lstadd_back_malloc(malloc_lst, ft_lstnew_malloc(result->content));
	ft_lstadd_back_malloc(malloc_lst, ft_lstnew_malloc(result));
	return (result);
}

t_lexed_list	*ft_lstlast_lexer(t_lexed_list *lst)
{
	t_lexed_list	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	lstadd_back_lexer(t_lexed_list **lst, t_lexed_list *new)
{
	t_lexed_list	*last;

	if (*lst)
	{
		last = ft_lstlast_lexer(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void ft_read_lst(t_lexed_list *lst)
{
	while (lst)
	{
		printf("type=%d %s\n", lst->operator, lst->content);
		lst = lst->next;
	}
}

void free_lst(t_lexed_list *lst)
{
	t_lexed_list *tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst->content);
		free(lst);
		lst = tmp;
	}
}