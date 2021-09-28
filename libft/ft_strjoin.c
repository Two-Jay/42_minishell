/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 05:39:20 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 03:04:45 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*set_memory(const char *s1, const char *s2,
		unsigned int *s1_l, unsigned int *s2_l)
{
	char	*ret;

	*s1_l = ft_strlen(s1);
	*s2_l = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (*s1_l + *s2_l + 1));
	if (!ret)
		return (NULL);
	return (ret);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*ret;
	unsigned int	s1_l;
	unsigned int	s2_l;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1 || !s2)
	{
		if (!(s1))
			return (ft_strdup(s2));
		else
			return (ft_strdup(s1));
	}
	ret = set_memory(s1, s2, &s1_l, &s2_l);
	if (!ret)
		return (NULL);
	while (*s1)
		*(ret++) = *(s1++);
	while (*s2)
		*(ret++) = *(s2++);
	*ret = '\0';
	return (ret);
}
