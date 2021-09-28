/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 08:44:53 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:52:55 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *src, int c)
{
	if (!src)
		return (NULL);
	while (*src && *src != (char)c)
		src++;
	if (*src == (char)c)
		return ((char *)src);
	return (NULL);
}
