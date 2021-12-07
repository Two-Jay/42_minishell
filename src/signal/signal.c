/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:00 by jekim             #+#    #+#             */
/*   Updated: 2021/12/07 21:45:30 by jekim            ###   ########.fr       */
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
        ft_putstr_fd(PROMPT, STDOUT_FILENO);
        ft_putstr_fd("\n", STDOUT_FILENO);
        g_dq = DQ_SIGINT;
    }
    else
    {
        tri(DQ_SIGINT);
    }

}

/*
** ctrl + \
*/
// void signal_handler_SIGQUIT(int signo)
// {
//     pid_t pid;
//     int state;
    
//     (void)signo;
//     pid = waitpid(-1, &state, WNOHANG);
//     if (pid == -1)
//     {
//         ft_putstr_fd(PROMPT, 1);
//     }
//     else
//     {
//         ft_putstr_fd(MSG_SIGQUIT, 1);
//         g_dq = DQ_SIGQUIT;
//     }
// }

/*
** ctrl + d
*/
void signal_handler_SIGTERM(int signo)
{
    (void)signo;
    printf("\b\bSIGTERM catched\n");
}


int set_signal_attr(void)
{
    struct termios attributes;
	struct termios saved;

    rl_catch_signals =0;
    tcgetattr(STDIN_FILENO, &saved);
    tcgetattr(STDIN_FILENO, &attributes);
    attributes.c_lflag &= (~ECHOCTL);
    tcsetattr(STDIN_FILENO, TCSANOW, &attributes);
    return (0);
}

int set_signal_handler(void)
{
    set_signal_attr();
    signal(SIGINT, signal_handler_SIGINT);
    // signal(SIGQUIT, signal_handler_SIGQUIT);
    signal(SIGTERM, signal_handler_SIGTERM);
    return (0);
}
