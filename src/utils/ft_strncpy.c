/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:34:52 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 17:14:35 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	ft_strnlen(const char *str, size_t n)
{
	size_t	ix;

	ix = 0;
	while (str[ix])
	{
		if (ix == n)
			break ;
		ix++;
	}
	return (ix);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	size;

	size = ft_strnlen(src, n);
	if (size != n)
		ft_memset(dst + size, '\0', n - size);
	return (ft_memcpy(dst, src, size));
}
