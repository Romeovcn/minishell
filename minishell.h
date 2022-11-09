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
# define PIPE 1 // pipe
# define REDIR_INPUT 2 // <
# define REDIR_OUTPUT 3 // >
# define HERE_DOC 4 // <<
# define APPEND_OUTPUT 5 // >>

typedef struct del_list
{
	char			*content;
	struct del_list 	*next;
}					t_del_list;

typedef struct outf_list
{
	char			*content;
	struct outf_list 	*next;
}					t_outf_list;

typedef struct inf_list
{
	char			*content;
	struct inf_list	*next;
}					t_inf_list;

typedef struct o_list
{
	char			*content;
	struct o_list 	*next;
}					t_options_list;

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

typedef struct env_list
{
	char			*content;
	struct env_list	*next;
}					t_env_list;

typedef struct t_list
{
	t_options_list	*options;

	int				input_fd;
	t_inf_list		*in_file;
	t_del_list		*delimiter;
	int				output_fd;
	t_outf_list		*out_file;
	struct t_list	*next;
}					t_token_list;

//----------------------------------------------------------------------------//
//						 			Utils				 					  //
//----------------------------------------------------------------------------//
void				free_string_array(char **array);
char				*ft_strjoin_char(char const *s1, char c);

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
void				get_env(t_env_list **env_lst, char **env, t_malloc_list **malloc_lst);
char				*get_env_value(char *name, t_env_list *env_lst);

//----------------------------------------------------------------------------//
//							 	Env lst			 							  //
//----------------------------------------------------------------------------//
t_env_list			*ft_lstnew_env(char *content, t_malloc_list **malloc_lst);
t_env_list			*ft_lstlast_env(t_env_list *lst);
void				ft_lstadd_back_env(t_env_list **lst, t_env_list *new);
void				ft_read_lst_env(t_env_list *lst);


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
void				token(t_lexed_list *lexed_lst, t_malloc_list **malloc_lst);

//----------------------------------------------------------------------------//
//							 	Token lst utils								  //
//----------------------------------------------------------------------------//
t_token_list		*ft_lstnew_token(t_malloc_list **malloc_lst);
t_token_list		*ft_lstlast_token(t_token_list *lst);
void				ft_lstadd_back_token(t_token_list **lst, t_token_list *new);
void				ft_read_lst_token(t_token_list *lst);
void				free_lst_token(t_token_list *lst);

//----------------------------------------------------------------------------//
//							 	Check error									  //
//----------------------------------------------------------------------------//
int					check_error(t_lexed_list *lexed_list);

//----------------------------------------------------------------------------//
//							 		Parsing									  //
//----------------------------------------------------------------------------//
void				parsing(t_lexed_list *lexer_lst, t_malloc_list **malloc_lst, t_env_list *env_lst);
int					is_env(char *str, int i);
char				*manage_quotes(char *str, t_malloc_list **malloc_lst, t_env_list *env_lst);

//----------------------------------------------------------------------------//
//							 	Malloc lst utils							  //
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
