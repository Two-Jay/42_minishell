/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 21:24:06 by jekim             #+#    #+#             */
/*   Updated: 2021/11/28 13:50:56 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

static long long	is_overflow_ll(char *str)
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
	if (minus == -1)
		return (256 - (converted % 256));
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

static void	exit_with_param(t_data *data)
{
	char		*str;
	long long	errno_converted;

	str = data->input->next->content;
	errno_converted = 0;
	write(1, "exit\n", 5);
	if (!is_num(str) || (ft_strlen(str) > 20)
		|| (ft_strlen(str) > 19 && *str != '-'))
	{
		builtin_error(data, str, EXIT_ERRNUM, 255);
		// $? 세팅: 255 (buitin_error 내부에서)
		exit(255);
	}
	else
	{
		errno_converted = is_overflow_ll(str);
		if (errno_converted < 0)
		{
			builtin_error(data, str, EXIT_ERRNUM, 255);
			//$? 세팅: 255 (buitin_error 내부에서)
			exit(255);
		}
	}
	//$? 세팅: errno_converted
	exit(errno_converted);
}

static void	exit_no_param(void)
{
	//$? 세팅: 0
	write(1, "exit\n", 5);
	exit(0);
}

int	minishell_exit(t_data *data)
{
	if (data->input->next)
	{
		if (data->input->next->next)
			builtin_error(data, 0, EXIT_ERRMANY, 1);
		else
			exit_with_param(data);
	}
	else
		exit_no_param();
	return (0);
}
