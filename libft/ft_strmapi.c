/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 22:46:41 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 03:01:35 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *src, char (*f)(unsigned int, char))
{
	char			*ret;
	unsigned int	ix;
	unsigned int	size;

	if (!src || !f)
		return (NULL);
	ix = 0;
	size = ft_strlen(src);
	ret = (char *)malloc(sizeof(char) * (size + 1));
	if (!ret)
		return (NULL);
	while (src[ix])
	{
		ret[ix] = (*f)(ix, src[ix]);
		ix++;
	}
	return (ret);
}
