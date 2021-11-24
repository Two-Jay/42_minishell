/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:09:26 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/23 15:17:35 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	builtin_error(t_data *data, char *value_str, char *error_str, int dollar_q)
{
	(void)dollar_q;
	ft_putstr_fd(data->input->content, 2);
	ft_putstr_fd(": ", 2);
	if (value_str)
		ft_putstr_fd(value_str, 2);
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
	// dq = dollar_q ($? 세팅)
	return (-1);
}
