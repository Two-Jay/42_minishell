/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:17:53 by jekim             #+#    #+#             */
/*   Updated: 2021/12/18 01:20:46 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler_interrupt_heredoc(int signo)
{
	if (signo == SIGINT)
	{
		g_dq = DQ_SIGINT;
		ft_putstr_fd("\n", STDOUT_FILENO);
		exit(1);
	}
}

void	set_signal_handler_ignore(int signo)
{
	if (signo == SIGUSR1)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	init_signal(int signo)
{
	if (signo == SIGUSR1)
		return ;
}

void	set_signal_handler_heredoc(void)
{	
	rl_catch_signals = 1;
	signal(SIGINT, signal_handler_interrupt_heredoc);
	signal(SIGQUIT, SIG_IGN);
}
