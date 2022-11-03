#include "minishell.h"

void manage_operator(char **readline_str, t_lexed_list **lexed_lst, char **test)
{
	if ((*readline_str)[1] && (*readline_str)[0] == '<' && (*readline_str)[1] == '<')
	{
		ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(ft_strdup("<<"), HERE_DOC));
		(*readline_str)++;
	}
	else if ((*readline_str)[1] && (*readline_str)[0] == '>' && (*readline_str)[1] == '>')
	{
		ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(ft_strdup(">>"), APPEND_OUTPUT));
		(*readline_str)++;
	}
	else if ((*readline_str)[0] == '|')
		ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(ft_strdup("|"), PIPE));
	else if ((*readline_str)[0] == '<') 
		ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(ft_strdup("<"), REDIR_INPUT));
	else if ((*readline_str)[0] == '>')
		ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(ft_strdup(">"), REDIR_OUTPUT));
	(*readline_str)++;
}

char *manage_word(char *readline_str, t_lexed_list **lexed_lst)
{
	char *word;
	int size;

	size = get_word_size(readline_str);
	word = malloc((size + 1) * sizeof(char));
	get_word(readline_str, &word);
	ft_lstadd_back_lexer(lexed_lst, ft_lstnew_lexer(word, WORD));
}

t_lexed_list *lexer(char *readline_str)
{
	t_lexed_list *lexed_lst;
	char *str;

	lexed_lst = NULL;
	while (*readline_str)
	{
		if (is_operator(readline_str))
			manage_operator(&readline_str, &lexed_lst, &readline_str);
		else if (ft_isprint(*readline_str) && *readline_str != ' ' && !is_operator(readline_str))
		{
			manage_word(readline_str, &lexed_lst);
			go_to_word_end(&readline_str);
			// printf("next=%s\n", readline_str);
			// break ;
		}
		else
			readline_str++;
	}
	return (lexed_lst);
}