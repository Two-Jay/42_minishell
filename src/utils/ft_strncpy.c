/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:34:52 by jekim             #+#    #+#             */
/*   Updated: 2021/11/25 19:51:15 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t ft_strnlen(const char *str, size_t n)
{
	size_t ix;

	ix = 0;
	while (str[ix])
	{
		if (ix == n)
			break ;
		ix++;
	}
	return (ix);
}

char *ft_strncpy(char *s1, const char *s2, size_t n)
{
	size_t size;

	size = ft_strnlen(s2, n);
	if (size != n)
		ft_memset(s1 + size, '\0', n - size);
	return (ft_memcpy(s1, s2, size));
}
