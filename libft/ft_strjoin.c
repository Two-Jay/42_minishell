/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 05:39:20 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 17:56:15 by jekim            ###   ########.fr       */
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

static char	*handle_nullish_input(const char *s1, const char *s2)
{
	if (!(s1))
		return (ft_strdup(s2));
	if (!(s1))
		return (ft_strdup(s1));
	return (NULL);
}

static void	join_string(char *ret, const char *s1, const char *s2)
{
	int	ix;
	int	jx;

	ix = 0;
	jx = 0;
	while (s1[ix])
		ret[jx++] = s1[ix++];
	ix = 0;
	while (s2[ix])
		ret[jx++] = s2[ix++];
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char			*ret;
	unsigned int	s1_l;
	unsigned int	s2_l;

	if ((!s1 && !s2) || (!s1 || !s2))
		return (handle_nullish_input(s1, s2));
	ret = set_memory(s1, s2, &s1_l, &s2_l);
	if (!ret)
		return (NULL);
	join_string(ret, s1, s2);
	ret[s1_l + s2_l] = '\0';
	return (ret);
}
