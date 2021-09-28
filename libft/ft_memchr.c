/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 23:40:43 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:51:02 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *src, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	find;

	if (!src)
		return (NULL);
	s = (unsigned char *)src;
	find = c;
	while (n--)
	{
		if (*s != find)
			s++;
		else
			return (s);
	}
	return (0);
}
