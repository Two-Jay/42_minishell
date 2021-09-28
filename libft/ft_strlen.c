/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 00:30:31 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 03:01:19 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *src)
{
	const char	*tmp;

	tmp = src;
	if (!src)
		return (0);
	while (*tmp++)
		;
	return ((size_t)(tmp - src - 1));
}
