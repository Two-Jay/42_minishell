/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/01 00:33:17 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:52:56 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		len;

	if (!s)
		return (NULL);
	len = (int)ft_strlen(s);
	ret = (char *)malloc(len + 1);
	ft_memcpy(ret, s, (len + 1));
	return (ret);
}
