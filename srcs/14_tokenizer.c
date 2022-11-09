#include "minishell.h"

void token(t_lex_lst *lexed_lst, t_mal_lst **mal_lst)
{
	t_tok_list *token;
	t_tok_list *head;

	token = NULL;
	lstadd_back_token(&token, lstnew_token(mal_lst));
	head = token;
	printf("--------Command lst token--------\n");

	while (lexed_lst)
	{
		if (lexed_lst->operator == PIPE)
		{
			printf("New token created\n");
			read_lst_array(token->options, "options");
			printf("intput_fd: %d\n", token->input_fd);
			read_lst_array(token->delimiter, "delimiter");
			read_lst_array(token->in_file, "in_file");
			printf("output_fd: %d\n", token->output_fd);
			read_lst_array(token->out_file, "out_file");
			printf("-----------------\n");
			lstadd_back_token(&token, lstnew_token(mal_lst));
			token = token->next;
			lexed_lst = lexed_lst->next;
			continue;
		}
		if (lexed_lst->operator == HERE_DOC)
		{
			token->input_fd = HERE_DOC;
			lexed_lst = lexed_lst->next;
			lstadd_back_array(&token->delimiter, lstnew_array(lexed_lst->content, mal_lst));
			lexed_lst = lexed_lst->next;
			continue;
		}
		if (lexed_lst->operator == REDIR_INPUT)
		{
			token->input_fd = REDIR_INPUT;
			lexed_lst = lexed_lst->next;
			lstadd_back_array(&token->in_file, lstnew_array(lexed_lst->content, mal_lst));
			lexed_lst = lexed_lst->next;
			continue;
		}
		if (lexed_lst->operator == REDIR_OUTPUT)
		{
			token->output_fd = REDIR_OUTPUT;
			lexed_lst = lexed_lst->next;
			lstadd_back_array(&token->out_file, lstnew_array(lexed_lst->content, mal_lst));
			lexed_lst = lexed_lst->next;
			continue;
		}
		if (lexed_lst->operator == APPEND_OUTPUT)
		{
			token->output_fd = APPEND_OUTPUT;
			lexed_lst = lexed_lst->next;
			lstadd_back_array(&token->out_file, lstnew_array(lexed_lst->content, mal_lst));
			lexed_lst = lexed_lst->next;
			continue;
		}
		if (lexed_lst->operator == WORD)
		{
			lstadd_back_array(&token->options, lstnew_array(lexed_lst->content, mal_lst));
			lexed_lst = lexed_lst->next;
			continue;
		}
	}
	printf("New token created\n");
	read_lst_array(token->options, "options");
	printf("intput_fd: %d\n", token->input_fd);
	read_lst_array(token->delimiter, "delimiter");
	read_lst_array(token->in_file, "in_file");
	printf("output_fd: %d\n", token->output_fd);
	read_lst_array(token->out_file, "out_file");
	printf("-----------------\n");
}