/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:29:52 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:45:42 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

char	*ft_define_base_arr(t_info *info)
{
	if (info->type == 'd' || info->type == 'i' || info->type == 'u')
		return (DEC);
	else if (info->type == 'x' || info->type == 'p')
		return (HEX_L);
	else if (info->type == 'X')
		return (HEX_U);
	else
		return (NULL);
}

int	ft_define_base_l(t_info *info)
{
	if (info->type == 'd' || info->type == 'i' || info->type == 'u')
		return (10);
	else if (info->type == 'x' || info->type == 'X' || info->type == 'p')
		return (16);
	else
		return (0);
}

int	ft_intlen(long long nbr, int base_l, t_info *info)
{
	int			len;

	len = 1;
	if (info->precision == 0 && nbr == 0)
		return (0);
	else
	{
		nbr = nbr / base_l;
		while (nbr)
		{
			nbr = nbr / base_l;
			len++;
		}
	}
	return (len);
}

int	ft_write_padding(t_info *info, int pad_l)
{
	int		ret;
	char	padding;

	ret = 0;
	padding = ' ';
	if (info->zeropad == TRUE)
		padding = '0';
	while (ret < pad_l)
		ret += write(1, &padding, 1);
	return (ret);
}

int	ft_handle_null_d(t_info *info)
{
	int		ix;
	char	padding;

	ix = 0;
	padding = ' ';
	if (info->zeropad == TRUE)
		padding = '0';
	while (ix < info->width)
		ix += write(1, &padding, 1);
	return (ix);
}
