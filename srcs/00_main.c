/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/05 18:42:52 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_empty_line(char *rl_str) // to fix
{
	int	i;

	i = 0;
	while (*rl_str)
	{
		if (!ft_isspace(*rl_str))
			return (0);
		rl_str++;
	}
	if (i == 0)
		return (1);
	return (1);
}

int main(int argc, char **argv, char **env)
{
	t_exec		exec_struct;
	char 		*readline_str;
	int			status = 0;

	exec_struct.env_lst = NULL;
	exec_struct.env_lst = get_env_lst(env);

	signal_manager();
	readline_str = readline("Minishell> ");
	while (readline_str)
	{
		add_history(readline_str);
		if (check_empty_line(readline_str))
		{
			free(readline_str);
			readline_str = readline("Minishell> ");
			continue ;
		}
		exec_struct.mal_lst = NULL;
		exec_struct.lex_lst = lexer(readline_str, &exec_struct.mal_lst);
		if (check_error(exec_struct.lex_lst))
		{
			free_lst_malloc(exec_struct.mal_lst);
			free(readline_str);
			readline_str = readline("Minishell> ");
			continue ;
		}
		parser(exec_struct.lex_lst, &exec_struct.mal_lst, exec_struct.env_lst, WEXITSTATUS(status));
		exec_struct.tok_lst = get_token_lst(exec_struct.lex_lst, &exec_struct.mal_lst);
		init_exec(&exec_struct, env);
		exec(exec_struct);
		free_lst_malloc(exec_struct.mal_lst);
		free(readline_str);
		readline_str = readline("minishell> ");
	}
	if (!readline_str)
		write(1, "exit\n", 6);
	free_env_lst(exec_struct.env_lst);
}
