/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:05:39 by jekim             #+#    #+#             */
/*   Updated: 2021/10/10 19:52:48 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_closed(const char *input)
{
	int	ix;
	int	flag;

	flag = 0;
	ix = -1;
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
}

char *get_buf_without_rslash(const char *input)
{
	int ix;
	int len;
	int flag;
	char *ret;

	ix = 0;
	len = 0;
	flag = 0;
	while (input[ix])
	{
		is_quoted(input[ix], &flag);
		if (!(input[ix] == (char)92 && flag == 0))
			len++;
		ix++;
	}
	ret = (char *)malloc(sizeof(char) * (len + 1));
	return (ret);
}

int	preprocess_input(const char *input, char *buf)
{
	int		ix;
	int		jx;
	int		flag;

	if (is_closed(input))
		return (ERROR_OCCURED);
	ix = 0;
	jx = 0;
	flag = 0;
	buf = get_buf_without_rslash(input);
	while (input[ix])
	{
		is_quoted(input[ix], &flag);
		if (!(input[ix] == (char)92 && flag == 0))
			buf[jx++] = input[ix];
		ix++;
	}
	buf[ix] = '\0';
	return (0);
}

int	parse_input(const char *input)
{
	char *buf;

	buf = NULL;
	if (preprocess_input(input, buf))
		return (1);
	return (0);
}