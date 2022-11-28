#include "minishell.h"

void	command(t_exec *exec, int i)
{
	char	**args;
	char	*path;

	path = find_right_access(getenv("PATH"), exec->tok_lst->args);
	args = lst_to_str_array(exec->tok_lst->args, &exec->mal_lst);
	if (exec->tok_lst->output_fd == 1 && i != exec->nb_command - 1)
	{
		printf("pas bon %d\n", i);
		dup2(exec->fd[1], STDOUT_FILENO);
	}
	close_fd(exec->fd[0], exec->fd[1]);
	execve(path, args, exec->envp);
	execve(path, args, exec->envp);
	exit(0);
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

void	here_doc(char *delimiter)
{
	char	*line;
	int		len;
	int		here_doc_fd;

	here_doc_fd = open(delimiter, O_CREAT | O_RDWR, 0666);
	line = get_next_line(0);
	delimiter = ft_strjoin(delimiter, "\n");
	while (line)
	{
		if (ft_strmatch(delimiter, line))
			break ;
		ft_putstr_fd(line, here_doc_fd);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(here_doc_fd);
}

void	redir_out(t_exec *exec)
{
	char	*file;
	int		file_fd;

	file = lstlast_array(exec->tok_lst->out_file)->content;
	file_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (exec->tok_lst->args != NULL)
	{
		printf("redir out duping\n");
		dup2(file_fd, STDOUT_FILENO);
	}
}

void	redir_in(t_exec *exec)
{
	char	*file;
	int		file_fd;

	file = lstlast_array(exec->tok_lst->in_file)->content;
	file_fd = open(file, O_RDONLY);
	if (exec->tok_lst->args != NULL)
		dup2(file_fd, STDIN_FILENO);
}
