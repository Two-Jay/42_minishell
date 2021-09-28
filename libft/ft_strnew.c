/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 03:05:59 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 03:01:50 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(char *str, size_t strlen)
{
	char	*ret;
	size_t	ix;

	ix = 0;
	ret = (char *)malloc(sizeof(char) * (strlen + 1));
	if (!ret)
		return (NULL);
	while (ix < strlen)
	{
		ret[ix] = str[ix];
		ix++;
	}
	str[ix] = '\0';
	return (ret);
}
