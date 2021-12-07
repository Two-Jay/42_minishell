/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:00 by jekim             #+#    #+#             */
/*   Updated: 2021/12/07 15:26:48 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** ctrl + c
*/
void signal_handler_SIGINT(int signo)
{
    pid_t pid;
    int state;
    
    (void)signo;
    pid = waitpid(-1, &state, WNOHANG);
    if (pid == -1)
    {
        erase_current_term_line();
        ft_putstr_fd(PROMPT, 1);
        g_dq = DQ_SIGINT;
    }
    else
    {
        erase_current_term_line();
        // ft_putstr_fd("\b\b  \b\b", 1);
        ft_putchar_fd('c', 1);
        ft_putstr_fd(PROMPT, 1);
        g_dq = DQ_SIGINT;
    }
}

/*
** ctrl + \
*/
void signal_handler_SIGQUIT(int signo)
{
    pid_t pid;
    int state;
    
    (void)signo;
    pid = waitpid(-1, &state, WNOHANG);
    if (pid == -1)
    {
        ft_putstr_fd("\b\b  \b\b", 1);
    }
    else
    {
        ft_putstr_fd("Quit: 3", 1);
        g_dq = DQ_SIGQUIT;
    }
}

/*
** ctrl + d
*/
void signal_handler_SIGTERM(int signo)
{
    (void)signo;
    printf("\b\bSIGTERM catched\n");
}

int set_signal_handler(void)
{
    signal(SIGINT, signal_handler_SIGINT);
    signal(SIGQUIT, signal_handler_SIGQUIT);
    signal(SIGTERM, signal_handler_SIGTERM);
    return (0);
}