/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 22:13:30 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:48:08 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

int	ft_define_widthpad_l_nbr(t_info *info, int nbr_l)
{
	int	ret;

	ret = info->width;
	if (info->input_negative == TRUE || (info->input_negative == FALSE
			&& info->sign != 0))
		ret -= (1 + ft_getmax(info->precision, nbr_l));
	else
		ret -= ft_getmax(info->precision, nbr_l);
	if (ret < 0)
		return (0);
	else
		return (ret);
}

int	ft_define_prcspad_l_nbr(t_info *info, int nbr_l)
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

static void	ft_define_is_negative(t_info *info, long long nbr)
{
	if (nbr < 0)
		info->input_negative = TRUE;
	else
		info->input_negative = FALSE;
}

long long	ft_handle_input(t_info *info, va_list *ap)
{
	long long	nbr;

	if (info->type == 'u' || info->type == 'x' || info->type == 'X')
		nbr = (long long)va_arg(*ap, unsigned int);
	else
		nbr = (long long)va_arg(*ap, int);
	if (nbr < 0)
	{
		ft_define_is_negative(info, nbr);
		nbr *= -1;
		if (info->zeropad == TRUE)
		{
			info->zeropad = FALSE;
			if (info->precision == -1)
			{
				info->precision = info->width - 1;
				info->width = 0;
			}
		}
	}
	return (nbr);
}
