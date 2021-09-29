/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isoverflow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 01:12:55 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 03:58:53 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./libft.h"

int	ft_isoverflow(long long nbr)
{
	long long	max;
	long long	min;

	max = 2147483647;
	min = -2147483648;
	if (nbr > max)
		return (1);
	if (nbr < min)
		return (-1);
	else
		return (0);
}
