/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:09:26 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/03 00:14:10 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	builtin_error(char *cmd, char *error_str, int dollar_q)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
	if (error_str)
		free(error_str);
	return (-1);
}

int	child_error(char *cmd, char *error_str, int dollar_q)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
	free(error_str);
	return (dollar_q);
}
