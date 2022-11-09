#include "minishell.h"

// int get_del_size(t_lexed_list *lexed_lst)
// {
// 	int size;

// 	size = 0;
// 	while (lexed_lst)
// 	{
// 		if (lexed_lst->operator == HERE_DOC)
// 			size++;
// 		lexed_lst = lexed_lst->next;
// 	}
// 	return (size);
// }

// int get_del_size(t_lexed_list *lexed_lst)
// {
// 	int size;

// 	size = 0;
// 	while (lexed_lst)
// 	{
// 		if (lexed_lst->operator == HERE_DOC)
// 			size++;
// 		lexed_lst = lexed_lst->next;
// 	}
// 	return (size);
// }

int get_cmd_size(t_lexed_list *lexed_lst)
{
	int size;

	size = 0;
	while (lexed_lst)
	{
		if (lexed_lst->operator == PIPE)
		 	return (size);
		else if (lexed_lst->operator != WORD)
		{
			lexed_lst = lexed_lst->next->next;
		}
		else
		{
			printf("content=%s\n", lexed_lst->content);
			lexed_lst = lexed_lst->next;
		}
	}
}

void token(t_lexed_list *lexed_lst, t_malloc_list **malloc_lst)
{
	t_token_list *token;
	t_token_list *head;

	token = NULL;
	ft_lstadd_back_token(&token, ft_lstnew_token(malloc_lst));
	head = token;
	printf("--------Command lst token--------\n");

	// printf("del size=%d\n", get_del_size(lexed_lst));
	get_cmd_size(lexed_lst);
	// while (lexed_lst)
	// {
	// 	if (lexed_lst->operator == PIPE)
	// 	{
	// 		// printf("new token input=%d delimiter=%s in_file=%s output=%d out_file=%s\n", token->input_fd, token->delimiter, token->in_file, token->output_fd, token->out_file);
	// 		ft_lstadd_back_token(&token, ft_lstnew_token(malloc_lst));
	// 		token = token->next;
	// 	}
	// 	// if (lexed_lst->operator == HERE_DOC && lexed_lst->next)
	// 	// {
	// 	// 	token->input_fd = HERE_DOC;
	// 	// 	lexed_lst = lexed_lst->next;
	// 	// 	token->delimiter = lexed_lst->content;
	// 	// 	lexed_lst = lexed_lst->next;
	// 	// 	continue;
	// 	// }
	// 	// if (lexed_lst->operator == REDIR_INPUT && lexed_lst->next)
	// 	// {
	// 	// 	token->input_fd = REDIR_INPUT;
	// 	// 	lexed_lst = lexed_lst->next;
	// 	// 	token->in_file = lexed_lst->content;
	// 	// 	lexed_lst = lexed_lst->next;
	// 	// 	continue;
	// 	// }
	// 	// if (lexed_lst->operator == REDIR_OUTPUT && lexed_lst->next)
	// 	// {
	// 	// 	token->output_fd = REDIR_OUTPUT;
	// 	// 	lexed_lst = lexed_lst->next;
	// 	// 	token->out_file = lexed_lst->content;
	// 	// 	lexed_lst = lexed_lst->next;
	// 	// 	continue;
	// 	// }
	// 	// if (lexed_lst->operator == APPEND_OUTPUT && lexed_lst->next)
	// 	// {
	// 	// 	token->output_fd = APPEND_OUTPUT;
	// 	// 	lexed_lst = lexed_lst->next;
	// 	// 	token->out_file = lexed_lst->content;
	// 	// 	lexed_lst = lexed_lst->next;
	// 	// 	continue;
	// 	// }
	// 	// if ()
	// 		// printf("operator=%d\n", lexed_lst->operator);
	// 	lexed_lst = lexed_lst->next;
	// }
}