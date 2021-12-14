/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:00 by jekim             #+#    #+#             */
/*   Updated: 2021/12/14 20:35:38 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void signal_handler_default_SIGINT(int signo)
{
    (void)signo;
    ft_putchar_fd('\n', STDOUT_FILENO);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    g_dq = 1;
}

void set_signal_handler_default(void)
{
    rl_catch_signals = 0;
    signal(SIGINT, signal_handler_default_SIGINT);
    signal(SIGQUIT, SIG_IGN);
}

void signal_handler_blocked_cmd(int signo)
{
    if (signo == SIGINT)
    {
        ft_putstr_fd("sigint checked\n", STDOUT_FILENO);
        g_dq = DQ_SIGINT;
    }
    else if (signo == SIGQUIT)
    {
        ft_putstr_fd("Quit : (__Core_dump_number)\n", STDOUT_FILENO);
        g_dq = DQ_SIGQUIT;
    }
}

void set_signal_handler_blocked_cmd(void)
{
    signal(SIGINT, signal_handler_blocked_cmd);
    signal(SIGQUIT, signal_handler_blocked_cmd);
}

void    set_signal_handler_ignore(int signo)
{
    if (signo == SIGUSR1)
    {
        signal(SIGINT, SIG_IGN);
        signal(SIGQUIT, SIG_IGN);
    }
}

void signal_handler_interrupt_heredoc(int signo)
{
    (void)signo;
    ft_putchar_fd(EOF, STDIN_FILENO);
    g_dq = DQ_SIGINT;
}

void set_signal_handler_heredoc(void)
{
    signal(SIGINT, signal_handler_interrupt_heredoc);
}