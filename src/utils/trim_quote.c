/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 17:57:38 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 18:45:06 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

char	*trim_quote(char *str)
{
	char	quote;
	int		i;
	int		length;
	char	*str_ret;

	if (*str == 34 || *str == 39)
	{
		length = ft_strlen(str) - 2;
		str++;
	}
	else
		length = ft_strlen(str);
	str_ret = malloc(sizeof(char) * (length + 1));
	if (!str_ret)
		return (NULL);
	i = -1;
	while (++i < length)
		str_ret[i] = *str++;
	str_ret[i] = 0;
	return (str_ret);
}
