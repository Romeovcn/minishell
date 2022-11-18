/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:14:18 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/18 18:19:33 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(t_exec *exec)
{
	char	**arg;
	char	*path;

	path = find_right_access(getenv("PATH"), exec->tok_lst->args);
	arg = lst_to_str_array(exec->tok_lst->args, &exec->mal_lst);
	execve(path, arg, exec->envp);
}

void	redir_out(t_exec *exec)
{
	char	*file;
	int		file_fd;

	if (pipe(exec->fd) == -1)
		return ;
	file = exec->tok_lst->out_file->content;
	file_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (exec->tok_lst->args != NULL)
	{
		dup2(file_fd, STDOUT_FILENO);
		command(exec);
	}
	close_fd(exec->fd[0], exec->fd[1]);
}

void	redir_in(t_exec *exec)
{
	char	*file;
	int		file_fd;

	if (pipe(exec->fd) == -1)
		return ;
	file = exec->tok_lst->in_file->content;
	file_fd = open(file, O_RDONLY);
	if (exec->tok_lst->args != NULL)
	{
		dup2(file_fd, STDIN_FILENO);
		command(exec);
	}
	close_fd(exec->fd[0], exec->fd[1]);
}

void	simple_exec(t_exec *exec)
{
	char	*path;
	char	**arg;

	if (exec->tok_lst->output_fd < 2 && exec->tok_lst->input_fd < 2)
	{
		printf("commande\n");
		command(exec);
	}
	else if (exec->tok_lst->output_fd == 3)
	{
		printf("redirection out\n");
		redir_out(exec);
	}
	else if (exec->tok_lst->input_fd == 2)
	{
		printf("redirection in\n");
		redir_in(exec);
	}
}

void	pipex_exec(t_exec *exec)
{
}

void	init_exec(t_exec *exec, t_tok_lst *tok_lst, t_mal_lst *mal_lst, char **envp)
{
	exec->tok_lst = tok_lst;
	exec->mal_lst = mal_lst;
	exec->pid = malloc(ft_lstsize_token(tok_lst) * sizeof(pid_t));
	if (!exec->pid)
		return ;
	exec->envp = envp;
}

int	exec(t_tok_lst *tok_lst, char **envp, t_mal_lst *mal_lst)
{
	int		lst_size;
	int		i;
	int		status;
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (0);
	init_exec(exec, tok_lst, mal_lst, envp);
	lst_size = ft_lstsize_token(tok_lst);
	printf("token size: %d\n", lst_size);
	// printf("token 1: %s\n", tok_lst->args->content);
	// printf("token 2: %s\n", tok_lst->next->args->content);
	if (lst_size == 1)
		simple_exec(exec);
	else if (lst_size > 1)
		pipex_exec(exec);
	i = 0;
	// while (i < lst_size)
	// {
	// 	waitpid(exec->pid[i], &status, 0);
	// 	i++;
	// }
	return (status);
}
