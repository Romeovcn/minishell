/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/15 18:43:48 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int G_STATUS = 0;

int check_empty_line(char *rl_str)
{
	int	i;

	i = 0;
	while (rl_str[i])
	{
		if (!ft_isspace(rl_str[i]))
			return (0);
		i++;
	}
	free(rl_str);
	return (1);
}

int main(int argc, char **argv, char **env)
{
	t_exec		exec_struct;
	char 		*readline_str;

	G_STATUS = 0;
	exec_struct.env_lst = get_env_lst(env);
	exec_struct.envp = envp_to_str_array(exec_struct.env_lst, NULL);
	while (1)
	{
		// signal_manager();
		signal(SIGINT, handler);
		signal(SIGQUIT, SIG_IGN);
		rl_outstream = stderr;
		readline_str = readline("Minishell> ");
		if (!readline_str)
			break ;
		add_history(readline_str);
		if (check_empty_line(readline_str))
			continue ;
		exec_struct.mal_lst = NULL;
		exec_struct.lex_lst = lexer(readline_str, &exec_struct.mal_lst);
		if (check_error(exec_struct.lex_lst))
		{
			free_lst_malloc(exec_struct.mal_lst);
			free(readline_str);
			continue ;
		}
		parser(exec_struct.lex_lst, &exec_struct.mal_lst, exec_struct.env_lst);
		exec_struct.tok_lst = get_token_lst(exec_struct.lex_lst, &exec_struct.mal_lst);
		init_exec(&exec_struct);
		exec(&exec_struct);
		free_lst_malloc(exec_struct.mal_lst);
		free(readline_str);
	}
	free_array(exec_struct.envp);
	free_env_lst(exec_struct.env_lst);
	ft_putstr_fd("exit\n", 2);
}
