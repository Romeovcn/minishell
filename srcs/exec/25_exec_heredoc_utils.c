/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_exec_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:50:56 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/29 16:09:25 by jsauvage         ###   ########.fr       */
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

char	*get_heredoc_name(int i)
{
	char	*heredoc_name;

	heredoc_name = malloc(sizeof(char) * 10);
	heredoc_name = ".heredoc";
	heredoc_name = ft_strjoin(heredoc_name, ft_itoa(i));
	return (heredoc_name);
}

t_array_lst	*get_here_doc_lst(t_exec *exec)
{
	t_tok_lst	*tmp;
	t_array_lst	*tmp_del;
	t_array_lst	*delimiter;
	int			i;

	delimiter = NULL;
	tmp = exec->tok_lst;
	i = 0;
	while (tmp)
	{
		tmp_del = tmp->delimiter;
		while (tmp_del)
		{
			lstadd_back_array(&delimiter,
				lstnew_array_content2(tmp_del->content,
					get_heredoc_name(i), &exec->mal_lst));
			tmp_del = tmp_del->next;
			i++;
		}
		tmp = tmp->next;
	}
	return (delimiter);
}

void	get_here_doc_file(char *delimiter, char *name_file)
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

void	heredoc_rm(t_array_lst *here_doc_lst)
{
	while (here_doc_lst)
	{
		printf("heredoc: %s\n", here_doc_lst->content2);
		unlink(here_doc_lst->content2);
		here_doc_lst = here_doc_lst->next;
	}
}
