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
# define PIPE 1 
# define REDIR_INPUT 2 // <
# define REDIR_OUTPUT 3 // >
# define HERE_DOC 4 // <<
# define APPEND_OUTPUT 5 // >>

typedef struct m_list
{
	void			*adr;
	struct m_list	*next;
}					t_malloc_list;

typedef struct l_list
{
	char			*content;
	int				operator;
	struct l_list	*next;
}					t_lexed_list;

typedef struct t_list
{
	char			**token;

	int				input_fd;
	char			**in_file;
	char			**delimiter;
	int				output_fd;
	char			**out_file;
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
t_lexed_list		*lexer(char *readline_str, t_malloc_list **malloc_lst);

//----------------------------------------------------------------------------//
//							 	Lexer lst utils								  //
//----------------------------------------------------------------------------//
t_lexed_list		*lstnew_lexer(void *content, int operator, t_malloc_list **malloc_lst);
t_lexed_list		*ft_lstlast_lexer(t_lexed_list *lst);
void				lstadd_back_lexer(t_lexed_list **lst, t_lexed_list *new);
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

//----------------------------------------------------------------------------//
//							 	Check error									  //
//----------------------------------------------------------------------------//
int					check_error(t_lexed_list *lexed_list);

//----------------------------------------------------------------------------//
//							 	Token lst utils								  //
//----------------------------------------------------------------------------//
t_malloc_list		*ft_lstnew_malloc(void *adr);
t_malloc_list		*ft_lstlast_malloc(t_malloc_list *lst);
void				ft_lstadd_back_malloc(t_malloc_list **lst, t_malloc_list *new);
void				free_lst_malloc(t_malloc_list *lst);

// To do :
// Env in linked list
// cas tricky : <<$env
// cas tricky : << end << end << env = ctrl c should exit all
// "" | ""
#endif
