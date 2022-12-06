/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 01:00:00 by rvincent          #+#    #+#             */
/*   Updated: 2022/12/06 19:02:34 by jsauvage         ###   ########.fr       */
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

struct termios termios_save;
sig_atomic_t the_flag = 0;

void reset_the_terminal(void)
{
	tcsetattr(0, 0, &termios_save );
}

void handle_the_stuff(int num)
{
	char buff[4];
	buff[0] = '[';
	buff[2] = '0' + num%10;
	num /= 10;
	buff[1] = '0' + num%10;
	buff[3] = ']';
	write(0, buff, sizeof buff);
	the_flag = 1;
}

int main(int argc, char **argv, char **env)
{
	t_exec		exec_struct;
	char 		*readline_str;

	int rc;
	int ch;
	struct termios termios_new;

	tcgetattr(0, &termios_save );
	atexit(reset_the_terminal);
	termios_new = termios_save;
	termios_new.c_lflag &= ~ECHOCTL;
	tcsetattr(0, 0, &termios_new );

	exec_struct.env_lst = get_env_lst(env);
	signal_manager();
	while (1)
	{
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
