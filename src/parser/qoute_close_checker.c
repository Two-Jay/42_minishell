/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoute_close_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 12:17:07 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 16:22:34 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	check_qoutation_mark(char *input, int ix, int *flag)
{
	if (is_single_quote(input, ix))
	{
		if (flag == 0)
			flag = 1;
		else if (flag == 1)
			flag = 0;
	}
	if (is_double_quote(input, ix))
	{
		if (flag == 0)
			flag = 2;
		else if (flag == 2)
			flag = 0;
	}
}

int	is_closed(const char *input)
{
	int	ix;
	int	flag;

	flag = 0;
	ix = -1;
	if (ft_strlen(input) == 1
		&& (is_single_quote(input, 0) || is_double_quote(input, 0)))
		return (FALSE);
	while (input[++ix])
		check_qoutation_mark(input, ix, &flag);
	if (!flag)
		return (TRUE);
	return (FALSE);
}
