/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:17:53 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 17:50:45 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler_interrupt_heredoc(int signo)
{
	(void)signo;
	exit(DQ_SIGINT);
	g_dq = DQ_SIGINT;
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
	signal(SIGINT, signal_handler_interrupt_heredoc);
}
