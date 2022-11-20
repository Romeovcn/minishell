/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:14:18 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/18 18:57:16 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_exec(t_exec *exec)
{
	char	*path;
	char	**arg;

	if (exec->tok_lst->output_fd < 2 && exec->tok_lst->input_fd < 2)
	{
		printf("commande\n");
		printf("arg: %s\n", exec->tok_lst->args->content);
		command(exec);
	}
	else if (exec->tok_lst->output_fd == 3)
	{
		printf("redirection out\n");
		redir_out(exec);
		if (exec->tok_lst->args != NULL)
			command(exec);
	}
	else if (exec->tok_lst->input_fd == 2)
	{
		printf("redirection in\n");
		redir_in(exec);
		if (exec->tok_lst->args != NULL)
			command(exec);
	}
	else if (exec->tok_lst->input_fd == 4)
	{
		printf("here_doc");
		here_doc(exec);
		unlink(".here_doc");
	}
	else if (exec->tok_lst->output_fd == 5)
	{
		printf("append\n");
		append(exec);
		if (exec->tok_lst->args != NULL)
			command(exec);
	}
	
}

void	fork_child(t_exec *exec, int i)
{
	exec->pid[i] = fork();
	// if (ft_crash_pid(exec->pid[i], exec->fd) == 0)
	// 	return (0);
	if (exec->pid[i] == 0)
		simple_exec(exec);
}

void	pipex_exec(t_exec *exec)
{
	t_exec	*tmp;
	int		i;

	tmp = exec;
	i = 0;
	while (i < tmp->nb_command)
	{
		if (pipe(tmp->fd) == -1)
			return ;
		fork_child(tmp, i);
		dup2(tmp->fd[0], STDIN_FILENO);
		close_fd(tmp->fd[0], tmp->fd[1]);
		i++;
		tmp->tok_lst = tmp->tok_lst->next;
	}
}

void	init_exec(t_exec *exec, t_tok_lst *tok_lst, t_mal_lst *mal_lst, char **envp)
{
	exec->tok_lst = tok_lst;
	exec->mal_lst = mal_lst;
	exec->nb_command = ft_lstsize_token(tok_lst);
	exec->pid = malloc(exec->nb_command * sizeof(pid_t));
	if (!exec->pid)
		return ;
	exec->envp = envp;
}

int	exec(t_tok_lst *tok_lst, char **envp, t_mal_lst *mal_lst)
{
	int		i;
	int		status;
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (0);
	init_exec(exec, tok_lst, mal_lst, envp);
	printf("token size: %d\n", exec->nb_command);
	// printf("token 1: %s\n", tok_lst->args->content);
	// printf("token 2: %s\n", tok_lst->next->args->content);
	if (exec->nb_command == 1)
		simple_exec(exec);
	else if (exec->nb_command > 1)
		pipex_exec(exec);
	i = 0;
	while (i < exec->nb_command)
	{
		waitpid(exec->pid[i], &status, 0);
		i++;
	}
	return (status);
}
