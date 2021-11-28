/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:09:26 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 21:57:22 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	builtin_error(char *cmd, char *error_str, int dollar_q)
{
	(void)dollar_q;
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
	// dq = dollar_q ($? 세팅)
	free(error_str);
	return (-1);
}
