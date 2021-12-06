/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:00:00 by jekim             #+#    #+#             */
/*   Updated: 2021/12/07 02:00:50 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** ctrl + c
*/
void signal_handler_SIGINT(int signo)
{
    (void)signo;
    printf("\b\b\n%s", PROMPT);
}

// /*
// ** ctrl + 
// */
// void signal_handler_SIGQUIT(int signo)
// {
//     (void)signo;
//     printf("SIGQUIT catched\n");
// }

/*
** ctrl + d
*/
void signal_handler_SIGTERM(int signo)
{
    (void)signo;
    printf("SIGTERM catched\n");
}

int set_signal_handler(void)
{
    signal(SIGINT, signal_handler_SIGINT);
    // signal(SIGQUIT, signal_handler_SIGQUIT);
    signal(SIGTERM, signal_handler_SIGTERM);
    return (0);
}