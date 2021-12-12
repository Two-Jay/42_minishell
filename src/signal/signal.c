/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:00 by jekim             #+#    #+#             */
/*   Updated: 2021/12/12 09:34:02 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** ctrl + c
*/
void signal_handler_SIGINT(int signo)
{
    (void)signo;
    ft_putchar_fd('\n', STDOUT_FILENO);
    rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
    g_dq = 1;
}

/*
** ctrl + d
*/
int set_signal_handler_default(void)
{
    signal(SIGINT, signal_handler_SIGINT);
    signal(SIGQUIT, SIG_IGN);
    return (0);
}

/*
** cmd 실행 이전에 넣을 것
*/
void signal_handler_blocked_cmd(int signo)
{
    if (signo == SIGQUIT)
    {
        ft_putstr_fd("Quit : (__Core_dump_number)\n", STDOUT_FILENO);
        g_dq = DQ_SIGQUIT;
    }
    else if (signo == SIGINT)
    {
        ft_putchar_fd('\n', STDOUT_FILENO);
        g_dq = DQ_SIGINT;
    }
}


void signal_handler_interrupt_heredoc(int signo)
{
    (void)signo;
    ft_putchar_fd('\n', STDOUT_FILENO);
    g_dq = DQ_SIGINT;
}

/*
** heredoc 실행시 이전에 넣을 것
*/
int set_signal_handler_heredoc(void)
{
    signal(SIGINT, signal_handler_interrupt_heredoc);
}