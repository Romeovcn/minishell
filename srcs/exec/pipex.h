/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 11:44:02 by jsauvage          #+#    #+#             */
/*   Updated: 2022/11/17 14:57:55 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>

typedef struct s_cmd
{
	char			*cmd;
	char			**arg;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_pipex
{
	int				fd_infile;
	int				fd_outfile;
	char			*infile;
	char			*outfile;
	char			*path;
	char			*access;
	int				status;
	t_cmd			*cmd;
	t_cmd			*cpy_head_cmd;
	int				nb_cmd;
	int				fd[2];
	pid_t			*pid;
	int				here_doc_bool;
	int				here_doc_fd;
}					t_pipex;

void				ft_init(char **av, int ac, t_pipex *pipex);
int					ft_pid_init(t_pipex *pipex);

int					ft_fork_parent(t_pipex *pipex, char **envp);
int					ft_check_here_doc(char **av, char **envp, t_pipex *pipex);

void				ft_parsing(char **envp, char **av, t_pipex *pipex, int ac);
void				ft_check_access(t_pipex *pipex);

int					ft_crash_pid(int pid, int fd[2]);
void				ft_exit_error(t_pipex *pipex, t_cmd *cmd, int i);

char				*ft_newstrjoin(char *s1, char *s2);
void				ft_free_linked_list(t_cmd **list);
void				ft_free(t_pipex *pipex, t_cmd *cmd);
void				ft_free_split(char **arr);

void				ft_close_fd(int fd1, int fd2);
void				ft_check_file(t_pipex *pipex, int i);
void				ft_dup(t_pipex *pipex, int i);

t_cmd				*ft_lstnew_cmd(void *content);
void				ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
int					ft_lstsize_cmd(t_cmd *lst);

#endif