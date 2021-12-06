/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:37:34 by jekim             #+#    #+#             */
/*   Updated: 2021/12/06 11:24:35 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_redirection(const char *str, int ix)
{
	if (ft_strequel(str + ix, ">") || ft_strequel(str + ix, "<"))
		return (1);
	if (ft_strequel(str + ix, ">>") || ft_strequel(str + ix, "<<"))
		return (2);
	return (0);
}

int is_pipe(const char *str, int ix)
{
	return (ft_strequel(str + ix, "|"));
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

int	print_syntax_error(char *cmd, char *error_str, t_data *data)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(error_str, 2);
	write(2, "\n", 1);
	// if (error_str)
	// 	free(error_str);
    data->dq = DQ_ERRSYNTAX;
	return (ERROR_OCCURED);
}