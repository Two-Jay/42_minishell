/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:57:38 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

static int	length_before_quote(char *str)
{
	int		length;
	char	quote;

	length = 0;
	if (*str == 34 || *str == 39)
	{
		quote = *str;
		str++;
		while (*str && *str != quote)
		{
			str++;
			length++;
		}
		return (length);
	}
	while (*str && *str != 34 && *str != 39)
	{
		str++;
		length++;
	}
	return (length);
}

static int	length_with_quote(char *str)
{
	int		length;
	char	quote;

	length = 0;
	if (*str == 34 || *str == 39)
	{
		quote = *str;
		str++;
		while (*str && *str != quote)
		{
			str++;
			length++;
		}
		length += 2;
		return (length);
	}
	while (*str && *str != 34 && *str != 39)
	{
		str++;
		length++;
	}
	return (length);
}

static int	count_quote_twin(char *str)
{
	char	quote;
	int		count;

	quote = 0;
	count = 0;
	while (*str)
	{
		if (*str == 34 || *str == 39)
		{
			if (quote == *str)
			{
				count++;
				quote = 0;
			}
			else if (!quote)
				quote = *str;
		}
		if (!quote && (*str != 34 && *str != 39)
			&& (*(str + 1) == 34 || *(str + 1) == 39))
			count++;
		str++;
	}
	return (count);
}

char	*trim_quote(char *str)
{
	int		i;
	int		length;
	char	*str_ret;

	length = length_before_quote(str);
	str_ret = malloc(sizeof(char) * (length + 1));
	if (!str_ret)
		return (NULL);
	if (*str == 34 || *str == 39)
		str++;
	i = -1;
	while (++i < length)
		str_ret[i] = *str++;
	str_ret[i] = 0;
	return (str_ret);
}

char	**trim_quote_and_parse(char *str)
{
	char	**token_set;
	int		token_count;
	int		i;

	token_count = count_quote_twin(str);
	token_set = malloc(sizeof(char *) * (token_count + 1));
	if (!token_set)
		return (NULL);
	i = -1;
	while (++i < token_count)
	{
		token_set[i] = trim_quote(str);
		str += length_with_quote(str);
	}
	token_set[i] = 0;
	return (token_set);
}
