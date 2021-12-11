/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:00 by jekim             #+#    #+#             */
/*   Updated: 2021/12/12 04:34:26 by jekim            ###   ########.fr       */
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
}

/*
** ctrl + d
*/

void *signal_handler_blocked_cmd(int signo)
{
    if (signo == SIGQUIT)
        ft_putstr_fd("^\\Quit : 3\n", STDOUT_FILENO);
    else if (signo == SIGINT)
        ft_putstr_fd("^C\n", STDOUT_FILENO);
    return (0);
}

int set_signal_handler(void)
{
    signal(SIGINT, signal_handler_SIGINT);
    signal(SIGQUIT, SIG_IGN);
    return (0);
}
