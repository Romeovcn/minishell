/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:45:32 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/05 21:50:19 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int num, siginfo_t *info, void *context)
{
	(void)context;
	if (num == SIGINT)
	{
		if (!info->si_pid)
		{
			int fd = open("/dev/null", O_RDONLY);
			dup2(fd, 0);
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
	else if (num == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(2, "", 1);
		// rl_replace_line("", 0);
	}
}

void	signal_manager()
{
	struct sigaction s_sig_okok;
	s_sig_okok.sa_sigaction = handle_sigint;
	s_sig_okok.sa_flags = SA_SIGINFO;
	// sigemptyset(&s_sig_okok.sa_mask);
	sigaction(SIGINT, &s_sig_okok, 0);
	sigaction(SIGQUIT, &s_sig_okok, 0);
}

// static void	handle_pid_sigint(int num)
// {
// 	write(1, "\n", 1);
// }

// void	signal_pid_manager()
// {
// 	signal(SIGINT, handle_pid_sigint);
// }
