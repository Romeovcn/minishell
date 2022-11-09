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

typedef struct a_list
{
	char			*content;
	struct a_list	*next;
}					t_array_lst;

typedef struct m_list
{
	void			*adr;
	struct m_list	*next;
}					t_mal_lst;

typedef struct l_list
{
	char			*content;
	int				operator;
	struct l_list	*next;
}					t_lex_lst;

typedef struct env_list
{
	char			*content;
	struct env_list	*next;
}					t_env_lst;

typedef struct t_list
{
	t_array_lst	*options;

	int				input_fd;
	t_array_lst	*in_file;
	t_array_lst	*delimiter;
	int				output_fd;
	t_array_lst	*out_file;
	struct t_list	*next;
}					t_tok_list;

//----------------------------------------------------------------------------//
//						 			Utils				 					  //
//----------------------------------------------------------------------------//
void		free_string_array(char **array);
char		*strjoin_char(char const *s1, char c, t_mal_lst **mal_lst);

//----------------------------------------------------------------------------//
//							 	Check access			 					  //
//----------------------------------------------------------------------------//
char		**get_paths(char **env);

//----------------------------------------------------------------------------//
//							 	Built-in			 						  //
//----------------------------------------------------------------------------//
void		ft_env(char **env);
void		ft_exit(t_command_data command_data);

//----------------------------------------------------------------------------//
//							 		Env			 							  //
//----------------------------------------------------------------------------//
void		get_env(t_env_lst **env_lst, char **env, t_mal_lst **mal_lst);
char		*get_env_value(char *name, t_env_lst *env_lst);

//----------------------------------------------------------------------------//
//							 	Env lst			 							  //
//----------------------------------------------------------------------------//
t_env_lst	*lstnew_env(char *content, t_mal_lst **mal_lst);
t_env_lst	*lstlast_env(t_env_lst *lst);
void		lstadd_back_env(t_env_lst **lst, t_env_lst *new);
void		read_lst_env(t_env_lst *lst);

//----------------------------------------------------------------------------//
//							 		Lexer									  //
//----------------------------------------------------------------------------//
t_lex_lst	*lexer(char *readline_str, t_mal_lst **mal_lst);

//----------------------------------------------------------------------------//
//							 	Lexer lst utils								  //
//----------------------------------------------------------------------------//
t_lex_lst	*lstnew_lexer(void *content, int operator, t_mal_lst **mal_lst);
t_lex_lst	*lstlast_lexer(t_lex_lst *lst);
void		lstadd_back_lexer(t_lex_lst **lst, t_lex_lst *new);
void		read_lst(t_lex_lst *lst);
void		free_lst(t_lex_lst *lst);

//----------------------------------------------------------------------------//
//							 	Lexer utils									  //
//----------------------------------------------------------------------------//
int			is_operator(char *readline_str);
int			get_word_size(char *readline_str);
void		get_word(char *readline_str, char **word);
void		go_to_word_end(char **readline_str);

//----------------------------------------------------------------------------//
//							 		Token									  //
//----------------------------------------------------------------------------//
void		token(t_lex_lst *lexed_lst, t_mal_lst **mal_lst);

//----------------------------------------------------------------------------//
//							 	Token lst utils								  //
//----------------------------------------------------------------------------//
t_tok_list	*lstnew_token(t_mal_lst **mal_lst);
t_tok_list	*lstlast_token(t_tok_list *lst);
void		lstadd_back_token(t_tok_list **lst, t_tok_list *new);
void		read_lst_token(t_tok_list *lst);
void		free_lst_token(t_tok_list *lst);

//----------------------------------------------------------------------------//
//							 	Array lst utils								  //
//----------------------------------------------------------------------------//
t_array_lst	*lstnew_array(char *content, t_mal_lst **mal_lst);
t_array_lst	*lstlast_array(t_array_lst *lst);
void		lstadd_back_array(t_array_lst **lst, t_array_lst *new);
void		read_lst_array(t_array_lst *lst, char *type);

//----------------------------------------------------------------------------//
//							 	Check error									  //
//----------------------------------------------------------------------------//
int			check_error(t_lex_lst *lexed_list);

//----------------------------------------------------------------------------//
//							 		parser									  //
//----------------------------------------------------------------------------//
void		parser(t_lex_lst *lex_lst, t_mal_lst **mal_lst, t_env_lst *env_lst);
char		*manage_quotes(char *str, t_mal_lst **mal_lst, t_env_lst *env_lst);

//----------------------------------------------------------------------------//
//							 		parser utils							  //
//----------------------------------------------------------------------------//
int			is_env(char *str);
char		*get_env_name(char *str, t_mal_lst **mal_lst);
void		go_end_env_name(char **str);

//----------------------------------------------------------------------------//
//							 	Malloc lst utils							  //
//----------------------------------------------------------------------------//
t_mal_lst	*lstnew_malloc(void *adr);
t_mal_lst	*lstlast_malloc(t_mal_lst *lst);
void		lstadd_back_malloc(t_mal_lst **lst, t_mal_lst *new);
void		free_lst_malloc(t_mal_lst *lst);

// To do :
// Protect malloc
// cas tricky : <<$env
// cas tricky : << end << end << env = ctrl c should exit all
// "" | ""
// Norm
#endif
