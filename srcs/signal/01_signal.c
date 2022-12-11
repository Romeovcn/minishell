/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:45:32 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/11 18:34:18 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_signal(int signal, siginfo_t *info, void *context)
{
	(void)context;
	if (info->si_pid)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		G_STATUS = 33500;
	}
	else
	{
		// kill(1, SIGKILL);
		ft_putstr_fd("\n", 1);
		// printf("pid: %d\n", info->si_pid);
		// kill(info->si_pid, SIGQUIT);
		G_STATUS = 33500;
		// kill(0, SIGKILL);
	}
}

static void	handle_signal_hd(int signal, siginfo_t *info, void *context)
{
	int	fd;

	(void)context;
	if (signal == SIGINT)
	{
		fd = open("/dev/null", O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
		ft_putstr_fd("\n", 1);
		G_STATUS = 33500;
	}
	if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 0);
}

void sigquit_process(int sig)
{
	ft_putstr_fd("Quit (core dumped)\n", 1);
	G_STATUS = 33536;
}

void	signal_manager_hd()
{
	struct sigaction s_sig;

	s_sig.sa_sigaction = handle_signal_hd;
	s_sig.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sig.sa_mask);
	sigaction(SIGINT, &s_sig, 0);
	sigaction(SIGQUIT, &s_sig, 0);
}

void	signal_manager()
{
	struct sigaction s_sig;

	s_sig.sa_sigaction = handle_signal;
	s_sig.sa_flags = SA_SIGINFO;
	sigemptyset(&s_sig.sa_mask);
	sigaction(SIGINT, &s_sig, 0);
	signal(SIGQUIT, SIG_IGN);
}
