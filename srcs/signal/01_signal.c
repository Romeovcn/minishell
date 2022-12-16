/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:45:32 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/13 19:23:52 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_process(int sig_num)
{
	if (sig_num == SIGQUIT)
		G_STATUS = 131;
	else if (sig_num == SIGINT)
		G_STATUS = 130;
}

void	sig_int_rl(int sig_num)
{
	if (sig_num == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		G_STATUS = 130;
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
		G_STATUS = 777;
	}
	if (signal == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 0);
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
