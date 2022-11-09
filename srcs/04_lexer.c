#include "minishell.h"

void manage_operator(char **readline_str, t_lex_lst **lexed_lst, t_mal_lst **mal_lst)
{
	if ((*readline_str)[1] && (*readline_str)[0] == '<' && (*readline_str)[1] == '<')
	{
		lstadd_back_lexer(lexed_lst, lstnew_lexer(ft_strdup("<<"), HERE_DOC, mal_lst));
		(*readline_str)++;
	}
	else if ((*readline_str)[1] && (*readline_str)[0] == '>' && (*readline_str)[1] == '>')
	{
		lstadd_back_lexer(lexed_lst, lstnew_lexer(ft_strdup(">>"), APPEND_OUTPUT, mal_lst));
		(*readline_str)++;
	}
	else if ((*readline_str)[0] == '|')
		lstadd_back_lexer(lexed_lst, lstnew_lexer(ft_strdup("|"), PIPE, mal_lst));
	else if ((*readline_str)[0] == '<') 
		lstadd_back_lexer(lexed_lst, lstnew_lexer(ft_strdup("<"), REDIR_INPUT, mal_lst));
	else if ((*readline_str)[0] == '>')
		lstadd_back_lexer(lexed_lst, lstnew_lexer(ft_strdup(">"), REDIR_OUTPUT, mal_lst));
	(*readline_str)++;
}

char *manage_word(char *readline_str, t_lex_lst **lexed_lst, t_mal_lst **mal_lst)
{
	char *word;
	int size;

	size = get_word_size(readline_str);
	word = malloc((size + 1) * sizeof(char));
	get_word(readline_str, &word);
	lstadd_back_lexer(lexed_lst, lstnew_lexer(word, WORD, mal_lst));
}

t_lex_lst *lexer(char *readline_str, t_mal_lst **mal_lst)
{
	t_lex_lst *lexed_lst;
	char *str;

	lexed_lst = NULL;
	while (*readline_str)
	{
		if (is_operator(readline_str))
			manage_operator(&readline_str, &lexed_lst, mal_lst);
		else if (ft_isprint(*readline_str) && *readline_str != ' ' && !is_operator(readline_str))
		{
			manage_word(readline_str, &lexed_lst, mal_lst);
			go_to_word_end(&readline_str);
		}
		else
			readline_str++;
	}
	printf("--------Command lst lexed--------\n");
	read_lst(lexed_lst);
	return (lexed_lst);
}