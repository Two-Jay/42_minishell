/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:05:39 by jekim             #+#    #+#             */
/*   Updated: 2021/10/09 21:21:55 by jekim            ###   ########.fr       */
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
		if (input[ix] == 39)
		{
			if (flag == 0)
				flag = 1;
			if (flag == 1)
				flag = 0;
		}
		if (input[ix] == 34)
		{
			if (flag == 0)
				flag = 2;
			if (flag == 2)
				flag = 0;
		}
	}
	printf("%s %d\n", input, flag);
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