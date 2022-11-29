/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   25_exec_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:50:56 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/29 01:37:30 by rvincent         ###   ########.fr       */
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
		if (tmp->input_fd == HERE_DOC)
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (0);
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
	while (i < exec->nb_command)
	{
		tmp_del = tmp->delimiter;
		while (tmp_del)
		{
			lstadd_back_array(&delimiter, lstnew_array(tmp_del->content, &exec->mal_lst));
			tmp_del = tmp_del->next;
		}
		i++;
		tmp = tmp->next;
	}
	return (delimiter);
}

void	get_here_doc_file(char *delimiter)
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