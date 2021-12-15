/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:55:17 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 17:32:54 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_pipe_redirection(const char *str, int ix)
{
	int	red_ret;

	if (is_pipe(str, ix))
		return (1);
	red_ret = is_redirection(str, ix);
	if (red_ret)
		return (red_ret);
	return (0);
}

int	is_quotation(const char *str, int ix)
{
	return (is_double_quote(str, ix) || is_single_quote(str, ix));
}

int	is_double_quote(const char *str, int ix)
{
	return ((int)str[ix] == 34);
}

int	is_single_quote(const char *str, int ix)
{
	return ((int)str[ix] == 39);
}

void	is_inquoted(const char *str, int ix, int *flag)
{
	if (is_double_quote(str, ix))
	{
		if (*flag == 2)
			*flag = 0;
		else if (*flag == 0)
			*flag = 2;
	}
	if (is_single_quote(str, ix))
	{
		if (*flag == 1)
			*flag = 0;
		else if (*flag == 0)
			*flag = 1;
	}
}
