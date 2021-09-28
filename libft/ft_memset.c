/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 19:59:22 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:51:18 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dst, int c, size_t n)
{
	unsigned char	*temp;
	unsigned char	value;

	if (!dst)
		return (NULL);
	temp = dst;
	value = c;
	while (n--)
	{
		*temp++ = value;
	}
	return ((void *)dst);
}
