/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 21:24:06 by jekim             #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

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

static void	exit_with_param(t_token *input)
{
	char		*str;
	long long	errno_converted;

	str = input->next->content;
	errno_converted = 0;
	write(1, "exit\n", 5);
	if (!is_num(str) || (ft_strlen(str) > 20)
		|| (ft_strlen(str) > 19 && *str != '-'))
	{
		builtin_error("bash: exit: ", ft_strjoin(str, EXIT_ERRNUM), 255);
		exit(255);
	}
	else
	{
		errno_converted = is_overflow_ll(str);
		if (errno_converted < 0)
		{
			builtin_error("bash: exit: ", ft_strjoin(str, EXIT_ERRNUM), 255);
			exit(255);
		}
	}
	exit(errno_converted);
}

static void	exit_no_param(void)
{
	write(1, "exit\n", 5);
	exit(0);
}

int	minishell_exit(t_data *data, t_token *input)
{
	if (data->input->next)
	{
		if (data->input->next->next)
		{
			builtin_error("shell", ft_strjoin("exit: ", EXIT_ERRMANY), 1);
			data->dq = 1;
		}
		else
			exit_with_param(input);
	}
	else
		exit_no_param();
	return (0);
}
