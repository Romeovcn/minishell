#include "minishell.h"

t_env_list	*ft_lstnew_env(char *content, t_malloc_list **malloc_lst)
{
	t_env_list	*result;

	result = malloc(sizeof(t_env_list));
	if (!result)
		return (0);
	ft_lstadd_back_malloc(malloc_lst, ft_lstnew_malloc(result));
	result->content = content;
	result->next = NULL;
	return (result);
}

t_env_list	*ft_lstlast_env(t_env_list *lst)
{
	t_env_list	*head;

	if (lst == NULL)
		return (0);
	head = lst;
	while (head->next)
		head = head->next;
	return (head);
}

void	ft_lstadd_back_env(t_env_list **lst, t_env_list *new)
{
	t_env_list	*last;

	if (*lst)
	{
		last = ft_lstlast_env(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

void ft_read_lst_env(t_env_list *lst)
{
	int i = 0;

	while (lst)
	{
		printf("%s\n",  lst->content);
		lst = lst->next;
	}
}