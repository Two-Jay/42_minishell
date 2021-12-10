/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:37:34 by jekim             #+#    #+#             */
/*   Updated: 2021/12/10 23:52:17 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_redirection(const char *str, int ix)
{
	if (ft_strequel(&str[ix], ">") || ft_strequel(str + ix, "<"))
		return (1);
	if (ft_strequel(&str[ix], ">>") || ft_strequel(str + ix, "<<"))
		return (2);
	return (0);
}

int is_pipe(const char *str, int ix)
{
	return (ft_strequel(str + ix, "|"));
}

int is_pipe_redirection_middle_str(const char *str, int ix)
{
	int red_ret;

	if (is_pipe_middle_str(str, ix))
		return (1);
	red_ret = is_redirection_middle_str(str, ix);
	if (red_ret)
		return (red_ret);
	return (0);
}

int is_pipe_middle_str(const char *str, int ix)
{
	return (str[ix] == '|');
}

int is_redirection_middle_str(const char *str, int ix)
{
	if (str[ix] == '>')
	{
		if (str[ix + 1] && str[ix + 1] == '>')
			return (2);
		return (1);
	}
	if (str[ix] == '<')
	{
		if (str[ix + 1] && str[ix + 1] == '<')
			return (2);
		return (1);
	}
	return (0);
}

int is_pipe_redirection(const char *str, int ix)
{
	int red_ret;

	if (is_pipe(str, ix))
		return (1);
	red_ret = is_redirection(str, ix);
	if (red_ret)
		return (red_ret);
	return (0);
}

int is_quotation(const char *str, int ix)
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
