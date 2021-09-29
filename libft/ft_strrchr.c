/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 19:25:59 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 03:01:59 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *src, int c)
{
	unsigned int	src_l;

	if (!src)
		return (NULL);
	src_l = (unsigned int)ft_strlen(src);
	while (src_l != 0 && src[src_l] != (char)c)
		src_l--;
	if (src[src_l] == (char)c)
		return ((char *)src + src_l);
	return (NULL);
}
