/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:09:26 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/20 11:34:42 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	builtin_error(t_data *data, char *value_str, char *error_str, int dollar_q)
{
	ft_putstr_fd(data->input->content, 2);
	if (value_str)
	{
		ft_putstr_fd(value_str, 2);
	}
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
	// dq = dollar_q ($? 세팅)
}
