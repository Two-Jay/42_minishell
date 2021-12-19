/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termattr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:42:20 by jekim             #+#    #+#             */
/*   Updated: 2021/12/19 17:35:43 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	turnon_echoctl_termattr(void)
{
	struct termios	termattr;

	tcgetattr(STDOUT_FILENO, &termattr);
	termattr.c_lflag |= ECHOCTL;
	tcsetattr(STDOUT_FILENO, TCSANOW, &termattr);
}

void	turnoff_echoctl_termattr(void)
{
	struct termios	termattr;

	tcgetattr(STDOUT_FILENO, &termattr);
	termattr.c_lflag &= (~ECHOCTL);
	tcsetattr(STDOUT_FILENO, TCSANOW, &termattr);
}
