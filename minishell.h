#ifndef MINISHELL_H
# define MINISHELL_H

# include "./minishell_define.h"

//----------------------------------------------------------------------------//
//						 			Utils				 					  //
//----------------------------------------------------------------------------//
void		error_exit(t_mal_lst *mal_lst);
char		*strjoin_char(char const *s1, char c, t_mal_lst **mal_lst);
char		**lst_to_str_array(t_array_lst *lst, t_mal_lst **mal_lst);
//----------------------------------------------------------------------------//
//							 	Check access			 					  //
//----------------------------------------------------------------------------//
char		**get_paths(char **env);
//----------------------------------------------------------------------------//
//							 	Built-in			 						  //
//----------------------------------------------------------------------------//
void		ft_env(char **args, t_env_lst *env_lst);
void		ft_pwd(char **args);
void		ft_exit(char **args, int status, t_mal_lst *mal_lst, t_env_lst *env_lst);
void		ft_echo(char **cmd);
void		ft_cd(char *path);
//----------------------------------------------------------------------------//
//							 	Env			 								  //
//----------------------------------------------------------------------------//
void		get_env_lst(t_env_lst **env_lst, char **env, t_mal_lst **mal_lst);
char		*get_env_value(char *name, t_env_lst *env_lst);
void		export_env(t_env_lst **env_lst, t_mal_lst **mal_lst, char **args);
void		unset_env(t_env_lst **env_lst, char **args);
//----------------------------------------------------------------------------//
//							 	Env utils		 							  //
//----------------------------------------------------------------------------//
char		*get_env_name(char *env, t_mal_lst **mal_lst);
void		get_env_lst(t_env_lst **env_lst, char **env, t_mal_lst **mal_lst);
void		change_env_value(char *name, char *new_value, t_env_lst *env_lst);
char		*get_env_value(char *name, t_env_lst *env_lst);
void		free_env_lst(t_env_lst *env_lst);
//----------------------------------------------------------------------------//
//							 	Env lst			 							  //
//----------------------------------------------------------------------------//
t_env_lst	*lstnew_env(char *name, char *value, t_mal_lst **mal_lst);
t_env_lst	*lstlast_env(t_env_lst *lst);
void		lstadd_back_env(t_env_lst **lst, t_env_lst *new);
//----------------------------------------------------------------------------//
//							 	Lexer										  //
//----------------------------------------------------------------------------//
t_lex_lst	*lexer(char *readline_str, t_mal_lst **mal_lst);
//----------------------------------------------------------------------------//
//							 	Lexer lst utils								  //
//----------------------------------------------------------------------------//
t_lex_lst	*lstnew_lex(void *content, int operator, t_mal_lst **mal_lst);
t_lex_lst	*lstlast_lexer(t_lex_lst *lst);
void		lstadd_back_lex(t_lex_lst **lst, t_lex_lst *new);
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
//							 	Parser										  //
//----------------------------------------------------------------------------//
void		parser(t_lex_lst *lex_lst, t_mal_lst **mal_lst, t_env_lst *env_lst);
char		*manage_quotes(char *str, t_mal_lst **mal_lst, t_env_lst *env_lst);
//----------------------------------------------------------------------------//
//							 	Parser utils								  //
//----------------------------------------------------------------------------//
int			is_env(char *str);
char		*parse_env_name(char *str);
void		go_end_env_name(char **str);
//----------------------------------------------------------------------------//
//							 	Malloc lst utils							  //
//----------------------------------------------------------------------------//
t_mal_lst	*lstnew_malloc(void *adr);
t_mal_lst	*lstlast_malloc(t_mal_lst *lst);
void		lstadd_back_malloc(t_mal_lst **lst, t_mal_lst *new);
void		free_lst_malloc(t_mal_lst *lst);
//----------------------------------------------------------------------------//
//							 	Token										  //
//----------------------------------------------------------------------------//
t_tok_lst	*get_token_lst(t_lex_lst *lexed_lst, t_mal_lst **mal_lst);
//----------------------------------------------------------------------------//
//							 	Token utils									  //
//----------------------------------------------------------------------------//
void		add_here_doc(t_tok_lst **token, t_lex_lst **lex_lst, t_mal_lst **mal_lst);
void		add_redir_in(t_tok_lst **token, t_lex_lst **lex_lst, t_mal_lst **mal_lst);
void		add_redir_out(t_tok_lst **token, t_lex_lst **lex_lst, t_mal_lst **mal_lst);
void		add_app_out(t_tok_lst **token, t_lex_lst **lex_lst, t_mal_lst **mal_lst);
void		add_word(t_tok_lst **token, t_lex_lst **lex_lst, t_mal_lst **mal_lst);
//----------------------------------------------------------------------------//
//							 	Token lst utils								  //
//----------------------------------------------------------------------------//
t_tok_lst	*lstnew_token(t_mal_lst **mal_lst);
t_tok_lst	*lstlast_token(t_tok_lst *lst);
void		lstadd_back_token(t_tok_lst **lst, t_tok_lst *new);
void		read_lst_token(t_tok_lst *lst);
int			ft_lstsize_token(t_tok_lst *lst);
//----------------------------------------------------------------------------//
//							 	Exec										  //
//----------------------------------------------------------------------------//
int			exec(t_tok_lst *tok_lst, char **envp, t_mal_lst *mal_lst);
char		*find_right_access(char *path, t_array_lst *cmd);
//----------------------------------------------------------------------------//
//							 	Exec simple									  //
//----------------------------------------------------------------------------//
void	    get_here_doc_file(char *delimiter);
void	    command(t_exec *exec, int i);
void	    append(t_tok_lst *tok_lst);
void	    redir_out(t_tok_lst *tok_lst);
void	    redir_in(t_tok_lst *tok_lst);
void		here_doc(t_tok_lst *tok_lst);
//----------------------------------------------------------------------------//
//							 	Exec simple	management						  //
//----------------------------------------------------------------------------//
void	    exec_token(t_exec *exec, int i);
void        here_doc_manage(t_exec *exec);
//----------------------------------------------------------------------------//
//							 	Exec utils									  //
//----------------------------------------------------------------------------//
char		*ft_newstrjoin(char *s1, char *s2);
void		close_fd(int fd1, int fd2);
t_array_lst	*get_here_doc_lst(t_exec *exec);
int	        check_heredoc(t_exec *exec);
void	    position_last_heredoc(t_exec *exec);
// To do :
// ft_exit without args should exit last code status
// Protect malloc
// cas tricky : <<$env
// cas tricky : << end << end << env = ctrl c should exit all
// "" | ""
// Norm

#endif