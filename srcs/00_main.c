/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/10 18:39:54 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int G_STATUS = 0;

int check_empty_line(char *rl_str) // to fix
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
	while (1)
	{
		signal_manager();
		printf("status=%d\n", G_STATUS);
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
		parser(exec_struct.lex_lst, &exec_struct.mal_lst, exec_struct.env_lst, WEXITSTATUS(G_STATUS));
		exec_struct.tok_lst = get_token_lst(exec_struct.lex_lst, &exec_struct.mal_lst);
		init_exec(&exec_struct, env);
		exec(exec_struct);
		free_lst_malloc(exec_struct.mal_lst);
		free(readline_str);
	}
	free_env_lst(exec_struct.env_lst);
	write(1, "exit\n", 6);
}
