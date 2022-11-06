#include "minishell.h"

void manage_operator(char **readline_str, t_lexed_list **lexed_lst, t_malloc_list **malloc_lst)
{
	if ((*readline_str)[1] && (*readline_str)[0] == '<' && (*readline_str)[1] == '<')
	{
		ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(ft_strdup("<<"), HERE_DOC, malloc_lst));
		(*readline_str)++;
	}
	else if ((*readline_str)[1] && (*readline_str)[0] == '>' && (*readline_str)[1] == '>')
	{
		ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(ft_strdup(">>"), APPEND_OUTPUT, malloc_lst));
		(*readline_str)++;
	}
	else if ((*readline_str)[0] == '|')
		ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(ft_strdup("|"), PIPE, malloc_lst));
	else if ((*readline_str)[0] == '<') 
		ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(ft_strdup("<"), REDIR_INPUT, malloc_lst));
	else if ((*readline_str)[0] == '>')
		ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(ft_strdup(">"), REDIR_OUTPUT, malloc_lst));
	(*readline_str)++;
}

char *manage_word(char *readline_str, t_lexed_list **lexed_lst, t_malloc_list **malloc_lst)
{
	char *word;
	int size;

	size = get_word_size(readline_str);
	word = malloc((size + 1) * sizeof(char));
	get_word(readline_str, &word);
	ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(word, WORD, malloc_lst));
}

t_lexed_list *lexer(char *readline_str, t_malloc_list **malloc_lst)
{
	t_lexed_list *lexed_lst;
	char *str;

	lexed_lst = NULL;
	while (*readline_str)
	{
		if (is_operator(readline_str))
			manage_operator(&readline_str, &lexed_lst, malloc_lst);
		else if (ft_isprint(*readline_str) && *readline_str != ' ' && !is_operator(readline_str))
		{
			manage_word(readline_str, &lexed_lst, malloc_lst);
			go_to_word_end(&readline_str);
			// printf("next=%s\n", readline_str);
			// break ;
		}
		else
			readline_str++;
	}
	printf("--------Command lst lexed--------\n");
	ft_read_lst(lexed_lst);
	return (lexed_lst);
}