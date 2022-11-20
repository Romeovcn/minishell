#include "minishell.h"

void	command(t_exec *exec)
{
	char	**arg;
	char	*path;

	path = find_right_access(getenv("PATH"), exec->tok_lst->args);
	arg = lst_to_str_array(exec->tok_lst->args, &exec->mal_lst);
	if (exec->incr != exec->nb_command - 1)
		dup2(exec->fd[1], STDOUT_FILENO);
	close_fd(exec->fd[0], exec->fd[1]);
	execve(path, arg, exec->envp);
}

void	append(t_exec *exec)
{
	char	*file;
	int		file_fd;

	file = exec->tok_lst->out_file->content;
	file_fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (exec->tok_lst->args != NULL)
		dup2(file_fd, STDOUT_FILENO);
}

void	here_doc(t_exec *exec)
{
	char	*line;
	int		len;
	int		here_doc_fd;
	char	*delimiter;

	here_doc_fd = open(".here_doc", O_CREAT | O_RDWR, 0666);
	line = get_next_line(0);
	len = (int)ft_strlen(line) - 1;
	delimiter = exec->tok_lst->delimiter->content;
	if (len < (int)ft_strlen(delimiter))
		len = (int)ft_strlen(delimiter);
	while (ft_strncmp(delimiter, line, len) != 0)
	{
		ft_putstr_fd(line, here_doc_fd);
		free(line);
		line = get_next_line(0);
		len = (int)ft_strlen(line) - 1;
		if (len < (int)ft_strlen(delimiter))
			len = (int)ft_strlen(delimiter);
	}
	free(line);
	close (here_doc_fd);
	// here_doc_fd = open(".here_doc", O_RDWR, 0666);
}

void	redir_out(t_exec *exec)
{
	char	*file;
	int		file_fd;

	file = exec->tok_lst->out_file->content;
	file_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (exec->tok_lst->args != NULL)
		dup2(file_fd, STDOUT_FILENO);
}

void	redir_in(t_exec *exec)
{
	char	*file;
	int		file_fd;

	file = exec->tok_lst->in_file->content;
	file_fd = open(file, O_RDONLY);
	if (exec->tok_lst->args != NULL)
		dup2(file_fd, STDIN_FILENO);
}
