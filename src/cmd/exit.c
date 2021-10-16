/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 21:24:06 by jekim             #+#    #+#             */
/*   Updated: 2021/10/16 19:41:20 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

long long	is_overflow_ll(char *str)
{
	unsigned long long	converted;
	int					minus;

	converted = 0;
	minus = 1;
	if (*str == '-')
	{
		minus = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str <= '9' && *str >= '0')
		converted = converted * 10 + (*str++ - '0');
	if (converted > LLMAX && minus == 1)
		return (-1);
	if (converted - 1 > LLMAX && minus == -1)
		return (-1);
	return (converted % 256);
}

static int	is_num(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (*str > '9' || *str < '0')
			return (0);
		str++;
	}
	return (1);
}

void	exit_with_param(char *str)
{
	long long	errno_converted;

	errno_converted = 0;
	if (!is_num(str) || (ft_strlen(str) > 20)
		|| (ft_strlen(str) > 19 && *str != '-'))
		exit_perror(str);
	else
	{
		errno_converted = is_overflow_ll(str);
		if (errno_converted < 0)
			exit_perror(str);
		else
			write(1, "exit\n", 5);
	}
	exit(errno_converted);
}

void	exit_no_param(void)
{
	exit(0);
}

void	minishell_exit(t_data *data)
{
	if (data->input->next)
		exit_with_param(data->input->next);
	else
		exit_no_param();
}
