/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/11/29 01:25:27 by rvincent         ###   ########.fr       */
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
	char		cmd_line[] ="cat Makefile | echo bonjour";
	int			status;

	printf("%s\n", cmd_line);
// ---------------------------------------------------------- //
//							Env    			                  //
// ---------------------------------------------------------- //
	env_lst = NULL;
		mal_lst = NULL;
	get_env_lst(&env_lst, env, &mal_lst);
	// char *args[] = {"exit", NULL};
	// char *export[] = {"export", "1=2", "?=MORTY", "USER=EHOH", NULL};
	// export_env(&env_lst, &mal_lst, export);
	// unset_env(&env_lst, unset);
	// ft_env(test, env_lst);
	// ft_exit(args, 32256, mal_lst, env_lst);
// // ---------------------------------------------------------- //
// //							Lexer	                          //
// // ---------------------------------------------------------- //
// 	lexed_lst = lexer(cmd_line, &mal_lst);
// // ---------------------------------------------------------- //
// //							Check syntax error                //
// // ---------------------------------------------------------- //
// 	if (check_error(lexed_lst))
// 		return (free_lst_malloc(mal_lst), printf("EXIT BEBE\n"), 1);
// // ---------------------------------------------------------- //
// //							Parser				              //
// // ---------------------------------------------------------- //
// 	parser(lexed_lst, &mal_lst, env_lst);
// // ---------------------------------------------------------- //
// //							Tokenizer			              //
// // ---------------------------------------------------------- //
// 	token_lst = get_token_lst(lexed_lst, &mal_lst);
// // ---------------------------------------------------------- //
// //							Exec				              //
// // ---------------------------------------------------------- //
// 	status = exec(token_lst, env, &mal_lst);
// 	// lst_to_str_array(token_lst->args, &mal_lst);
// // ---------------------------------------------------------- //
// //							Free				              //
// // ---------------------------------------------------------- //
// 	free_lst_malloc(mal_lst);
// // ---------------------------------------------------------- //
// //							Readline			              //
// // ---------------------------------------------------------- //
	// test();
	// char *test[] = {"echo", "-nn", "", NULL};
	// ft_echo(test);
	// ft_cd("./srcs");
	// ft_pwd(env);

	// (void)argc;
	// (void)argv;

	readline_str = readline("Minishell> ");
	while (readline_str)
	{
		add_history(readline_str);
		printf("%s\n", readline_str);
		mal_lst = NULL;
		lexed_lst = lexer(readline_str, &mal_lst);
		if (check_error(lexed_lst))
		{
			free_lst_malloc(mal_lst);
			printf("EXIT BEBE\n");
			continue ;
		}
		parser(lexed_lst, &mal_lst, env_lst);
		token_lst = get_token_lst(lexed_lst, &mal_lst);
		status = exec(token_lst, env, &mal_lst);
		free_lst_malloc(mal_lst);
		free(readline_str);
		readline_str = readline("Minishell> ");
		// printf("%s ICI\n", readline_str);
	}
	free_env_lst(env_lst);
}