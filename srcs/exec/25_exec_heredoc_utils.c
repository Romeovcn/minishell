/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_exec_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:50:56 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/05 18:34:44 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_heredoc(t_exec *exec)
{
	t_tok_lst	*tmp;
	int			i;

	tmp = exec->tok_lst;
	i = 0;
	while (i < exec->nb_command)
	{
		if (tmp->delimiter)
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}

static char	*get_heredoc_name(int i)
{
	char	*heredoc_name;

	heredoc_name = malloc(sizeof(char) * 9);
	heredoc_name = ".heredoc";
	heredoc_name = ft_strjoin(heredoc_name, ft_itoa(i));
	return (heredoc_name);
}

static void	get_here_doc_file(char *delimiter, char *name_file)
{
	char	*line;
	int		len;
	int		here_doc_fd;

	here_doc_fd = open(name_file, O_CREAT | O_RDWR, 0666);
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

void	here_doc_manage(t_exec *exec)
{
	t_tok_lst	*tok_head;
	t_array_lst	*del_head;
	char		*here_doc_name;
	int			i;

	i = 0;
	tok_head = exec->tok_lst;
	while (exec->tok_lst)
	{
		del_head = exec->tok_lst->delimiter;
		while (exec->tok_lst->delimiter)
		{
			here_doc_name = get_heredoc_name(i);
			get_here_doc_file(exec->tok_lst->delimiter->content, here_doc_name);
			exec->tok_lst->delimiter->content2 = here_doc_name;
			exec->tok_lst->delimiter = exec->tok_lst->delimiter->next;
			i++;
		}
		exec->tok_lst->delimiter = del_head;
		exec->tok_lst = exec->tok_lst->next;
	}
	exec->tok_lst = tok_head;
}

void	heredoc_rm(t_tok_lst *tok_lst)
{
	while (tok_lst)
	{
		while (tok_lst->delimiter)
		{
			unlink(tok_lst->delimiter->content2);
			tok_lst->delimiter = tok_lst->delimiter->next;
		}
		tok_lst = tok_lst->next;
	}
}
