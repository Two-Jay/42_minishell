/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:09:26 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/02 17:28:36 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	builtin_error(t_data *data, char *cmd, char *error_str, int dollar_q)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
	data->dq = dollar_q;
	if (error_str)
		free(error_str);
	return (-1);
}

int	child_error(t_data *data, char *cmd, char *error_str, int dollar_q)
{
	(void)dollar_q;
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
	data->dq = dollar_q;
	free(error_str);
	return (dollar_q);
}
