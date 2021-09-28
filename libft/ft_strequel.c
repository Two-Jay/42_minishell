/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 03:01:59 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:53:16 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequel(const char *s1, const char *s2)
{
	size_t	i;
	size_t	size;

	i = 0;
	if (!s1 || !s2)
		return (0);
	size = ft_strlen(s1);
	if (size != ft_strlen(s2))
		return (0);
	while (i < size)
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}
