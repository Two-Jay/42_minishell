/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:09:26 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 18:38:26 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	minishell_perror(char *cmd, int err, int exit_status)
{
	char	*str;

	if (err < 0)
		str = strerror(errno);
	else
		str = strerror(err);
	write(2, cmd, ft_strlen(cmd));
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	return (exit_status);
}

int	minishell_error(char *cmd, char *str, int exit_status)
{
	write(2, cmd, ft_strlen(cmd));
	if (!str)
	{
		write(2, "Unknown Error", ft_strlen("Unknown Error"));
		write(2, "\n", 1);
	}
	else
	{
		write(2, str, ft_strlen(str));
		write(2, "\n", 1);
	}
	return (exit_status);
}
