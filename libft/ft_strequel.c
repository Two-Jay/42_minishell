/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 03:01:59 by jekim             #+#    #+#             */
/*   Updated: 2021/11/26 01:40:14 by jekim            ###   ########.fr       */
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
