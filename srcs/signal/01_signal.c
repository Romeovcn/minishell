/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsauvage <jsauvage@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 15:45:32 by jsauvage          #+#    #+#             */
/*   Updated: 2022/12/03 19:24:47 by jsauvage         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int num)
{
	write(STDOUT_FILENO, "\nminishell> ", 13);
}

static void handler_segfault(int num)
{
	write(STDOUT_FILENO, "Segmentation fault\n", 20);
	exit(1);
}

void	signal_manager()
{
	signal(SIGINT, handle_sigint);
	signal(SIGSEGV, handler_segfault);
}
