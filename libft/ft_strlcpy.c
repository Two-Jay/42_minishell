/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:09:51 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 03:01:02 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	src_l;
	size_t	ix;

	if (!dst || !src || !dstsize)
		return (0);
	ix = 0;
	src_l = ft_strlen(src);
	while (src[ix] && ix + 1 < dstsize && ix < src_l)
	{
		dst[ix] = src[ix];
		ix++;
	}
	if (dstsize > 0)
		dst[ix] = '\0';
	return (src_l);
}
