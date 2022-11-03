#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdbool.h>

typedef struct command_data
{
	char			**env;
	char			*readline_str;
}					t_command_data;

# define WORD 0 // file name ou command ou argument
# define STR_DQ 1 // str double quote
# define STR_SQ 2 // str single quote
# define PIPE 3 
# define REDIR_INPUT 4 // <
# define REDIR_OUTPUT 5 // >
# define HERE_DOC 6 // <<
# define APPEND_OUTPUT 7 // >>

typedef struct l_list
{
	char			*content;
	int				operator;
	struct l_list	*next;
}					t_lexed_list;

typedef struct t_list
{
	char			*command;
	char			*flags;
	char			*args;

	int				input;
	char			*filename;
	char			*delimiter;
	int				output;
	struct t_list	*next;
}					t_token_list;

//----------------------------------------------------------------------------//
//						 			Utils				 					  //
//----------------------------------------------------------------------------//
void				free_string_array(char **array);

//----------------------------------------------------------------------------//
//							 	Check access			 					  //
//----------------------------------------------------------------------------//
char				**get_paths(char **env);

//----------------------------------------------------------------------------//
//							 	Built-in			 						  //
//----------------------------------------------------------------------------//
void				ft_env(char **env);
void				ft_exit(t_command_data command_data);

//----------------------------------------------------------------------------//
//							 		Env			 							  //
//----------------------------------------------------------------------------//
char				**get_my_env(char **env);
char				**ft_export_env(char **env, char *new_line_str);

//----------------------------------------------------------------------------//
//							 		Lexer									  //
//----------------------------------------------------------------------------//
t_lexed_list		*lexer(char *readline_str);

//----------------------------------------------------------------------------//
//							 	Lexer lst utils								  //
//----------------------------------------------------------------------------//
t_lexed_list		*ft_lstnew_lexer(void *content, int operator);
t_lexed_list		*ft_lstlast_lexer(t_lexed_list *lst);
void				ft_lstadd_back_lexer(t_lexed_list **lst, t_lexed_list *new);
void				ft_read_lst(t_lexed_list *lst);
void				free_lst(t_lexed_list *lst);

//----------------------------------------------------------------------------//
//							 	Lexer utils									  //
//----------------------------------------------------------------------------//
int					is_operator(char *readline_str);
int					get_word_size(char *readline_str);
void				get_word(char *readline_str, char **word);
void				go_to_word_end(char **readline_str);

//----------------------------------------------------------------------------//
//							 		Token									  //
//----------------------------------------------------------------------------//
void				token(t_lexed_list *lexed_lst);

//----------------------------------------------------------------------------//
//							 	Token lst utils								  //
//----------------------------------------------------------------------------//
t_token_list		*ft_lstnew_token();
t_token_list		*ft_lstlast_token(t_token_list *lst);
void				ft_lstadd_back_token(t_token_list **lst, t_token_list *new);
void				ft_read_lst_token(t_token_list *lst);
void				free_lst_token(t_token_list *lst);

#endif
