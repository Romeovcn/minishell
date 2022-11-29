#include "minishell.h"

void	append(t_tok_lst *tok_lst)
{
	char	*file;
	int		file_fd;

	file = lstlast_array(tok_lst->out_file)->content;
	file_fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (tok_lst->args != NULL)
		dup2(file_fd, STDOUT_FILENO);
}

void here_doc(t_tok_lst *tok_lst)
{
	int fd_here_doc;

	fd_here_doc = open(lstlast_array(tok_lst->delimiter)->content, O_RDONLY);
	dup2(fd_here_doc, STDIN_FILENO);
}

void	redir_out(t_tok_lst *tok_lst)
{
	char	*file;
	int		file_fd;

	file = lstlast_array(tok_lst->out_file)->content;
	file_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (tok_lst->args != NULL)
	{
		//printf("redir out duping\n");
		dup2(file_fd, STDOUT_FILENO);
	}
}

void	redir_in(t_tok_lst *tok_lst)
{
	char	*file;
	int		file_fd;

	//printf("redirection in\n");
	file = lstlast_array(tok_lst->in_file)->content;
	file_fd = open(file, O_RDONLY);
	if (tok_lst->args != NULL)
		dup2(file_fd, STDIN_FILENO);
}
