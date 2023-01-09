/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2023/01/09 01:03:04 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status = 0;

int	check_empty_line(char *rl_str)
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

// void	print_tok(t_tok_lst *token)
// {
// 	printf("--------Command lst token--------\n");
// 	while (token)
// 	{
// 		read_lst_array(token->args, "args");
// 		printf("intput_fd: %d\n", token->input_fd);
// 		read_lst_array(token->delimiter, "delimiter");
// 		read_lst_array(token->in_file, "in_file");
// 		printf("output_fd: %d\n", token->output_fd);
// 		read_lst_array(token->out_file, "out_file");
// 		printf("-----------------\n");
// 		token = token->next;
// 	}
// }

int	parser(t_exec *exec, char *readline_str)
{
	exec->mal_lst = NULL;
	exec->lex_lst = lexer(readline_str, exec);
	if (check_error(exec->lex_lst))
	{
		free_lst_malloc(exec->mal_lst);
		free(readline_str);
		return (1);
	}
	expander(exec);
	exec->tok_lst = get_token_lst(exec);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_exec	exec_struct;
	char	*readline_str;

	(void)argc;
	(void)argv;
	exec_struct.env_lst = get_env_lst(env);
	exec_struct.envp = env;
	while (1)
	{
		signal(SIGINT, sig_int_rl);
		signal(SIGQUIT, SIG_IGN);
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
