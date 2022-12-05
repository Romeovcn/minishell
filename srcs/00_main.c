/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/03 19:51:24 by jsauvage         ###   ########.fr       */
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
	t_lex_lst	*lexed_lst;
	t_tok_lst	*token_lst;
	t_mal_lst 	*mal_lst;
	t_env_lst 	*env_lst;
	char 		*readline_str;
	int			status = 0;

	// printf("%s\n", cmd_line);
// ---------------------------------------------------------- //
//							Env    			                  //
// ---------------------------------------------------------- //
	env_lst = NULL;
	mal_lst = NULL;
	get_env_lst(&env_lst, env);
	// char *args[] = {"exit", NULL};
	// char *export[] = {"export", "1=2", "?=MORTY", "USER=EHOH", NULL};
	// export_env(&env_lst, &mal_lst, export);
	// unset_env(&env_lst, unset);
	// ft_env(test, env_lst);
	// ft_exit(args, 32256, mal_lst, env_lst);
	// ft_echo(test);

	signal_manager();
	readline_str = readline("Minishell> ");
	while (readline_str)
	{
		add_history(readline_str);
		if (check_empty_line(readline_str))
		{
			readline_str = readline("Minishell> ");
			continue ;
		}
		mal_lst = NULL;
		lexed_lst = lexer(readline_str, &mal_lst);
		if (check_error(lexed_lst))
		{
			free_lst_malloc(mal_lst);
			free(readline_str);
			readline_str = readline("Minishell> ");
			continue ;
		}
		parser(lexed_lst, &mal_lst, env_lst, WEXITSTATUS(status));
		token_lst = get_token_lst(lexed_lst, &mal_lst);
		status = exec(token_lst, env, &mal_lst, &env_lst);
		// printf("status=%d\n", WEXITSTATUS(status));
		free_lst_malloc(mal_lst);
		free(readline_str);
		readline_str = readline("Minishell> ");
	}
	free_env_lst(env_lst);
}