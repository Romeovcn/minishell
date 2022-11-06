#include "minishell.h"

void token(t_lexed_list *lexed_lst)
{
	t_token_list *token;
	t_token_list *head;

	token = NULL;
	ft_lstadd_back_token(&token, ft_lstnew_token());
	head = token;
	printf("--------Command lst token--------\n");
	while (lexed_lst)
	{
		if (lexed_lst->operator == PIPE)
		{
			printf("new token input=%d delimiter=%s in_file=%s output=%d out_file=%s\n", token->input, token->delimiter, token->in_file, token->output, token->out_file);
			ft_lstadd_back_token(&token, ft_lstnew_token());
			token = token->next;
		}
		if (lexed_lst->operator == HERE_DOC && lexed_lst->next)
		{
			token->input = HERE_DOC;
			lexed_lst = lexed_lst->next;
			token->delimiter = lexed_lst->content;
			lexed_lst = lexed_lst->next;
			continue;
		}
		if (lexed_lst->operator == REDIR_INPUT && lexed_lst->next)
		{
			token->input = REDIR_INPUT;
			lexed_lst = lexed_lst->next;
			token->in_file = lexed_lst->content;
			lexed_lst = lexed_lst->next;
			continue;
		}
		if (lexed_lst->operator == REDIR_OUTPUT && lexed_lst->next)
		{
			token->output = REDIR_OUTPUT;
			lexed_lst = lexed_lst->next;
			token->out_file = lexed_lst->content;
			lexed_lst = lexed_lst->next;
			continue;
		}
		if (lexed_lst->operator == APPEND_OUTPUT && lexed_lst->next)
		{
			token->output = APPEND_OUTPUT;
			lexed_lst = lexed_lst->next;
			token->out_file = lexed_lst->content;
			lexed_lst = lexed_lst->next;
			continue;
		}
		// if ()
			// printf("operator=%d\n", lexed_lst->operator);
		lexed_lst = lexed_lst->next;
	}
	// ft_read_lst_token(token);
	free_lst_token(head);
}