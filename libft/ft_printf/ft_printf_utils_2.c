/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 22:32:06 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:46:48 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_getmin(int nbr1, int nbr2)
{
	if (!nbr1 && !nbr2)
		return (0);
	if (!nbr1 && nbr2)
		return (nbr2);
	if (nbr1 && !nbr2)
		return (nbr1);
	if (nbr1 > nbr2)
		return (nbr2);
	else
		return (nbr1);
}

int	ft_getmax(int nbr1, int nbr2)
{
	if (!nbr1 && !nbr2)
		return (0);
	if (!nbr1 && nbr2)
		return (nbr2);
	if (nbr1 && !nbr2)
		return (nbr1);
	if (nbr1 < nbr2)
		return (nbr2);
	else
		return (nbr1);
}

int	ft_handle_null_addr(t_info *info, long long addr, int nbr_l)
{
	int	ret;

	ret = 0;
	if (info->left == TRUE)
		ret += ft_write_addr(info, addr, nbr_l);
	ret += ft_write_padding(info, ft_define_widthpad_l_addr(info, nbr_l));
	if (info->left == FALSE)
		ret += ft_write_addr(info, addr, nbr_l);
	return (ret);
}
