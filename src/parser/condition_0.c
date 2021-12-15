/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_0.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:48:19 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 17:31:56 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_redirection(const char *str, int ix)
{
	if (ft_strequel(&str[ix], ">") || ft_strequel(str + ix, "<"))
		return (1);
	if (ft_strequel(&str[ix], ">>") || ft_strequel(str + ix, "<<"))
		return (2);
	return (0);
}

int	is_pipe(const char *str, int ix)
{
	return (ft_strequel(str + ix, "|"));
}

int	is_pipe_redirection_middle_str(const char *str, int ix)
{
	int	red_ret;

	if (is_pipe_middle_str(str, ix))
		return (1);
	red_ret = is_redirection_middle_str(str, ix);
	if (red_ret)
		return (red_ret);
	return (0);
}

int	is_pipe_middle_str(const char *str, int ix)
{
	return (str[ix] == '|');
}

int	is_redirection_middle_str(const char *str, int ix)
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
