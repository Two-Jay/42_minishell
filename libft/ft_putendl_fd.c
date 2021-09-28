/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 05:35:01 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:51:24 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	char	endl;

	endl = '\n';
	if (fd < 0)
		return ;
	if (s)
	{
		while (*s)
			write(fd, s++, 1);
		write(fd, &endl, 1);
	}
}
