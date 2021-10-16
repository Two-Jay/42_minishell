/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:38:09 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 19:38:18 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

void	exit_perror(char *input)
{
	write(1, "exit: ", 6);
	write(1, input, ft_strlen(input));
	write(1, EXIT_ERRNUM, ft_strlen(EXIT_ERRNUM));
}
