/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:00 by jekim             #+#    #+#             */
/*   Updated: 2021/12/19 17:35:29 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler_default_SIGINT(int signo)
{
	if (signo == SIGINT)
	{
		ft_putchar_fd('\n', STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_dq = 1;
	}
}

void	set_signal_handler_default(void)
{
	rl_catch_signals = 0;
	turnon_echoctl_termattr();
	signal(SIGINT, signal_handler_default_SIGINT);
	signal(SIGQUIT, SIG_IGN);
}

void	signal_handler_blocked_cmd(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_dq = DQ_SIGINT;
	}
	else if (signo == SIGQUIT)
	{
		ft_putstr_fd("Quit : (__Core_dump_number)\n", STDOUT_FILENO);
		g_dq = DQ_SIGQUIT;
	}
}

void	set_signal_handler_blocked_cmd(void)
{
	turnon_echoctl_termattr();
	signal(SIGINT, signal_handler_blocked_cmd);
	signal(SIGQUIT, signal_handler_blocked_cmd);
}
