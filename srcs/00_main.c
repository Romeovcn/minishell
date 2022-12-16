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

int parser(t_exec *exec, char *readline_str)
{
	exec->mal_lst = NULL;
	exec->lex_lst = lexer(readline_str, &exec->mal_lst);
	if (check_error(exec->lex_lst))
	{
		free_lst_malloc(exec->mal_lst);
		free(readline_str);
		return (1);
	}
	expander(exec->lex_lst, &exec->mal_lst, exec->env_lst);
	exec->tok_lst = get_token_lst(exec->lex_lst, &exec->mal_lst);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_exec		exec_struct;
	char 		*readline_str;

	exec_struct.env_lst = get_env_lst(env);
	exec_struct.envp = env;
	while (1)
	{
		signal(SIGINT, sig_int_rl);
		signal(SIGQUIT, SIG_IGN);
		rl_outstream = stderr;
		readline_str = readline("Minishell> ");
		if (!readline_str)
			break ;
		add_history(readline_str);
		if (check_empty_line(readline_str))
			continue ;
		if (parser(&exec_struct, readline_str))
			continue ;
		init_exec(&exec_struct);
		exec(&exec_struct);
		free_lst_malloc(exec_struct.mal_lst);
	}
	free_env_lst(exec_struct.env_lst);
	ft_putstr_fd("exit\n", 2);
}
