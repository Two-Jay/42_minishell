/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 21:24:06 by jekim             #+#    #+#             */
/*   Updated: 2021/12/19 15:26:05 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static int	exit_with_param(t_token *input)
{
	char		*str;
	long long	errno_converted;
	t_token		*input_backup;

	input_backup = input;
	while (input && input->type != FLAG && input->type != STR)
		input = input->next;
	str = input->content;
	errno_converted = 0;
	if (!is_num(str) || (ft_strlen(str) > 20)
		|| (ft_strlen(str) > 19 && *str != '-') || is_overflow_ll(str) < 0)
	{
		builtin_error("bash: exit: ", ft_strjoin(str, EXIT_ERRNUM), 255);
		exit(255);
	}
	errno_converted = is_overflow_ll(str);
	if (check_arg_num(input_backup) > 1)
		return (builtin_error(
				"shell", ft_strjoin("exit: ", EXIT_ERRMANY), 1));
	exit(errno_converted);
	return (0);
}

int	minishell_exit(t_token *input, int if_pipe)
{
	int		argument_check;

	turnon_echoctl_termattr();
	if (!if_pipe)
		write(2, "exit\n", 5);
	argument_check = check_argument(input);
	if (argument_check == ARGUMENT_O || argument_check == FLAG_O)
		return (exit_with_param(input));
	else
		exit(0);
	return (0);
}
