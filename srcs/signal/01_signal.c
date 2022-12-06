/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:45:32 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/06 19:02:43 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(siginfo_t *info)
{
	int	fd;

	printf("pas bon\n");
	if (!info->si_pid)
	{
		int fd = open("/dev/null", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		write(1, "\n", 1);
	}
	else
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	handle_sigquit(siginfo_t *info)
{
	// struct termios	config;


	if (!info->si_pid)
		write(1, "Quit (core dumped)\n", 20);
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	handle_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (signal == SIGINT)
		handle_sigint(info);
	else if (signal == SIGQUIT)
		handle_sigquit(info);
}

void	signal_manager()
{
	struct sigaction s_sig_okok;
	s_sig_okok.sa_sigaction = handle_signal;
	s_sig_okok.sa_flags = SA_SIGINFO;
	// sigemptyset(&s_sig_okok.sa_mask);
	sigaction(SIGINT, &s_sig_okok, 0);
	sigaction(SIGQUIT, &s_sig_okok, 0);
}
