/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/28 15:56:27 by jsauvage         ###   ########.fr       */
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
			return (1);
		rl_str++;
	}
	if (i == 0)
		return (1);
	return (0);
}

int main(int argc, char **argv, char **env)
{
	t_lex_lst	*lexed_lst;
	t_tok_lst	*token_lst;
	t_mal_lst 	*mal_lst;
	t_env_lst 	*env_lst;
	char 		*readline_str;
	char		cmd_line[] ="< Makefile cat | wc -l";
	int			status;

	mal_lst = NULL;
	printf("%s\n", cmd_line);
// ---------------------------------------------------------- //
//							Env    			                  //
// ---------------------------------------------------------- //
	env_lst = NULL;
	char *args[] = {"exit", NULL};
	char *export[] = {"export", "1=2", "?=MORTY", "USER=EHOH", NULL};
	get_env_lst(&env_lst, env, &mal_lst);
	// export_env(&env_lst, &mal_lst, export);
	// unset_env(&env_lst, unset);
	// ft_env(test, env_lst);
	// ft_exit(args, 32256, mal_lst, env_lst);
// ---------------------------------------------------------- //
//							Lexer	                          //
// ---------------------------------------------------------- //
	lexed_lst = lexer(cmd_line, &mal_lst);
// ---------------------------------------------------------- //
//							Check syntax error                //
// ---------------------------------------------------------- //
	if (check_error(lexed_lst))
		return (free_lst_malloc(mal_lst), printf("EXIT BEBE\n"), 1);
// ---------------------------------------------------------- //
//							Parser				              //
// ---------------------------------------------------------- //
	parser(lexed_lst, &mal_lst, env_lst);
// ---------------------------------------------------------- //
//							Tokenizer			              //
// ---------------------------------------------------------- //
	token_lst = get_token_lst(lexed_lst, &mal_lst);
// ---------------------------------------------------------- //
//							Exec				              //
// ---------------------------------------------------------- //
	status = exec(token_lst, env, mal_lst);
	// lst_to_str_array(token_lst->args, &mal_lst);
// ---------------------------------------------------------- //
//							Free				              //
// ---------------------------------------------------------- //
	free_env_lst(env_lst);
	free_lst_malloc(mal_lst);
// ---------------------------------------------------------- //
//							Readline			              //
// ---------------------------------------------------------- //
	// test();
	// char *test[] = {"echo", "-nn", "", NULL};
	// ft_echo(test);
	// ft_cd("./srcs");
	// ft_pwd(env);

	// (void)argc;
	// (void)argv;

	// readline_str = readline("minishell> ");
	// while (readline_str)
	// {
	// 	printf("nl=%d\n", rl_on_new_line());
	// 	add_history(readline_str);
	// 	printf("%s\n", readline_str);
	// 	free(readline_str);
	// 	readline_str = readline("minishell> ");
	// }
}