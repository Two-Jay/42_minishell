/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:00 by jekim             #+#    #+#             */
/*   Updated: 2021/12/14 16:08:23 by jekim            ###   ########.fr       */
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

void signal_handler_blocked_cmd_SIGINT(int signo)
{
    (void)signo;
    ft_putstr_fd("\n", STDOUT_FILENO);
    g_dq = DQ_SIGINT;
}

void signal_handler_blocked_cmd_SIGQUIT(int signo)
{
    (void)signo;
    ft_putstr_fd("Quit : (__Core_dump_number)\n", STDOUT_FILENO);
    g_dq = DQ_SIGQUIT;
}

void set_signal_handler_blocked_cmd(t_token *token)
{
    pid_t pid;
    int status;

    pid = waitpid(-1, &status, WNOHANG);
    if (pid == -1 && !ft_strequel("./minishell", token->content))
    {
        signal(SIGINT, signal_handler_blocked_cmd_SIGINT);
        signal(SIGQUIT, signal_handler_blocked_cmd_SIGQUIT);
    }
    else
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