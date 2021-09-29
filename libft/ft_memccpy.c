/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:56:03 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:50:57 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	unsigned char	find;
	unsigned int	ix;

	d = dst;
	s = (unsigned char *)src;
	find = c;
	ix = 0;
	if (!dst && !src)
		return (NULL);
	while (ix < n)
	{
		d[ix] = s[ix];
		if (s[ix] == find)
			return (d + (ix + 1));
		ix++;
	}
	return (NULL);
}
