/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termattr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:42:20 by jekim             #+#    #+#             */
/*   Updated: 2021/12/18 16:04:56 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void backup_termattr(struct termios *termattr)
{
    static int flag;

    if (!flag)
    {
        tcgetattr(STDOUT_FILENO, termattr);        
        flag = 1;
    }
}

void reset_termattr(struct termios *termattr)
{
    tcsetattr(STDOUT_FILENO, 0, termattr);  
}

void turnoff_echoctl_termattr(void)
{
	struct termios	termattr;

	tcgetattr(STDOUT_FILENO, &termattr);
	termattr.c_lflag = ~(ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &termattr);    
}