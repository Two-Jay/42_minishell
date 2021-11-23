/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:37:34 by jekim             #+#    #+#             */
/*   Updated: 2021/11/23 18:52:25 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_pipe_redirection(const char *str, int ix, int str_l)
{
	if (str[ix] == '|')
		return (1);
	if (str[ix] == '>')
	{
		if (ix < str_l - 1 && str[ix + 1] == '>')
			return (2);
		return (1);
	}
	if (str[ix] == '<')
	{
		if (ix < str_l - 1 && str[ix + 1] == '<')
			return (2);
		return (1);
	}
	return (0);
}

int	is_double_quote(const char *str)
{
	return ((int)*str == 34);
}

int	is_single_quote(const char *str)
{
	return ((int)*str == 39);
}

void	is_inquoted(const char *str, int ix, int *flag)
{
	int double_quote_check;
	int single_quote_check;

	double_quote_check = is_double_quote(str + ix);
	single_quote_check = is_single_quote(str + ix);
	if (double_quote_check && *flag == 2)
		*flag = 0;
	if (single_quote_check && *flag == 1)
		*flag = 0;
	if (double_quote_check && *flag != 2)
		*flag = 2;
	if (single_quote_check && *flag != 1)
		*flag = 1;
}