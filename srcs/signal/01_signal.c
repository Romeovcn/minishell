/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:45:32 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/07 00:14:36 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(siginfo_t *info)
{
	int	fd;

		printf("%d\n", info->si_pid);
		// fd = open("/dev/null", O_RDONLY);
		// dup2(fd, STDIN_FILENO);
		// close(fd);
		write(1, "\n", 1);
	// else
	// {
		// write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	// }
}

static void	handle_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (signal == SIGINT)
		handle_sigint(info);
	else if (signal == SIGQUIT)
		write(1, "Quit (core dumped)\n", 20);
}

void	signal_manager_pid()
{
	struct sigaction s_sig;
	s_sig.sa_sigaction = handle_signal;
	s_sig.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &s_sig, 0);
	sigaction(SIGQUIT, &s_sig, 0);
}

void	signal_manager()
{
	struct sigaction s_sig;
	s_sig.sa_sigaction = handle_signal;
	s_sig.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &s_sig, 0);
	signal(SIGQUIT, SIG_IGN);
}
