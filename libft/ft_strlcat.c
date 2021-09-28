/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 20:03:42 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 03:00:55 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dst_l;
	size_t	src_l;
	size_t	ix;

	if (!src || !dst)
		return (0);
	dst_l = (unsigned int)ft_strlen(dst);
	src_l = (unsigned int)ft_strlen(src);
	ix = 0;
	if (n < dst_l)
		return (n + src_l);
	if (n > dst_l)
	{
		while (src[ix] && ix < (n - dst_l - 1))
		{
			dst[dst_l + ix] = src[ix];
			ix++;
		}
		dst[dst_l + ix] = '\0';
	}
	return (src_l + dst_l);
}
