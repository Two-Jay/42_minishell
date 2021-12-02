/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_close_checker.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 09:53:41 by jekim             #+#    #+#             */
/*   Updated: 2021/11/30 09:54:48 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_isclosed(const char *input)
{
	int	ix;
	int	flag;

	flag = 0;
	ix = -1;
	if (ft_strlen(input) == 1 && (input[0] == (char)39 || input[0] == (char)34))
		return (FALSE);
	while (input[++ix])
	{
		if (input[ix] == (char)39)
		{
			if (flag == 0)
				flag = 1;
			else if (flag == 1)
				flag = 0;
		}
		if (input[ix] == (char)34)
		{
			if (flag == 0)
				flag = 2;
			else if (flag == 2)
				flag = 0;
		}
	}
	if (flag == 0)
		return (TRUE);
	return (FALSE);
}