/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:05:39 by jekim             #+#    #+#             */
/*   Updated: 2021/10/10 15:10:32 by jekim            ###   ########.fr       */
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

int	preprocess_quote(const char *input, char *buf)
{
	size_t	len;

	if (is_closed(input))
		return (ERROR_OCCURED);
	len = ft_strlen(input);
	buf = (char *)ft_calloc(sizeof(char), len);
	return (0);
}

int	parse_input(const char *input)
{
	char *buf;

	buf = NULL;
	if (preprocess_quote(input, buf))
		return (1);
	return (0);
}