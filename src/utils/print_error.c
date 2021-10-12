/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 14:09:26 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/12 14:12:39 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

void	minishell_perror(char *cmd, int err)
{
	char	*str;

	if (!err)
		str = strerror(errno);
	else
		str = strerror(err);
	write(1, cmd, ft_strlen(cmd));
	write(1, str, ft_strlen(str));
	write(1, "\n", 1);
}
