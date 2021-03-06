/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_addr_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 22:13:30 by jekim             #+#    #+#             */
/*   Updated: 2021/12/11 00:30:27 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_define_widthpad_l_addr(t_info *info, int nbr_l)
{
	int	ret;

	ret = info->width - (nbr_l + 2);
	if (ret < 0)
		return (0);
	else
		return (ret);
}

int	ft_define_prcspad_l_addr(t_info *info, int nbr_l)
{
	int	ret;

	ret = info->precision - nbr_l;
	if (info->precision_minus == TRUE)
		ret = 0;
	if (ret < 0)
		return (0);
	else
		return (ret);
}

int	ft_write_addr_prefix(void)
{
	int	ret;

	ret = write(1, "0x", 2);
	return (ret);
}

long long	ft_handle_addr_input(va_list *ap)
{
	long long	nbr;

	nbr = va_arg(*ap, long long);
	return (nbr);
}
