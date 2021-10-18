/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 21:47:31 by jekim             #+#    #+#             */
/*   Updated: 2021/10/18 20:10:42 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_closed(const char *input)
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

void is_quoted(const char cha, int *flag)
{
	if (cha == (char)39)
	{
		if (*flag == 0)
			*flag = 1;
		else if (*flag == 1)
			*flag = 0;
	}
	if (cha == (char)34)
	{
		if (*flag == 0)
			*flag = 2;
		else if (*flag == 2)
			*flag = 0;
	}
	else
		*flag = 0;
}

void is_inquote(const char cha, int *flag)
{
	if (cha == (char)39)
	{
		if (*flag == 0)
			*flag = 1;
		else if (*flag == 1)
			*flag = 0;
	}
	if (cha == (char)34)
	{
		if (*flag == 0)
			*flag = 2;
		else if (*flag == 2)
			*flag = 0;
	}
}


int is_pipe_redirection(const char *target, int idx)
{
	if (target[idx] == '|')
		return (1);
	if (target[idx] == '>')
	{
		if (target[idx + 1] && target[idx + 1] == '>')
			return (2);
		return (1);
	}
	if (target[idx] == '<')
	{
		if (target[idx + 1] && target[idx + 1] == '<')
			return (2);
		return (1);
	}
	return (0);
}

int		is_envname_charset(char cha)
{
	return ((ft_isalpha(cha) || ft_isalnum(cha) || cha == '_'));
}