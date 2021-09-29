/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_nbr_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:23:17 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:47:40 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static void	ft_putnbr(long long nbr, int base_l, char *base)
{
	if (nbr >= base_l)
		ft_putnbr((nbr / base_l), base_l, base);
	ft_putchar_fd(base[nbr % base_l], 1);
}

static int	ft_write_sign(t_info *info)
{
	int	ret;

	ret = 0;
	if (info->input_negative == TRUE)
		ret += ft_putchar('-');
	else if (info->input_negative == FALSE && info->sign != 0)
		ret += ft_putchar(info->sign);
	return (ret);
}

static int	ft_write_prcspad(int prcspad_l)
{
	int	ret;

	ret = 0;
	while (ret < prcspad_l)
		ret += write(1, "0", 1);
	return (ret);
}

static int	ft_write_nbr(t_info *info, long long nbr, int nbr_l)
{
	int	ret;
	int	prcspad_l;
	int	base_l;

	ret = 0;
	prcspad_l = ft_define_prcspad_l_nbr(info, nbr_l);
	base_l = ft_define_base_l(info);
	ret += ft_write_sign(info);
	if (prcspad_l)
		ret += ft_write_prcspad(prcspad_l);
	ft_putnbr(nbr, base_l, ft_define_base_arr(info));
	ret += nbr_l;
	return (ret);
}

int	ft_print_nbr(t_info *info, va_list *ap)
{
	long long	nbr;
	char		*base;
	int			ret;
	int			base_l;
	int			nbr_l;

	if (info->zeropad == TRUE && info->precision >= 0)
		info->zeropad = FALSE;
	ret = 0;
	nbr = ft_handle_input(info, ap);
	base = ft_define_base_arr(info);
	base_l = ft_define_base_l(info);
	nbr_l = ft_intlen(nbr, base_l, info);
	if (nbr == 0 && info->precision == 0)
		return (ft_handle_null_d(info));
	if (info->left == TRUE)
		ret += ft_write_nbr(info, nbr, nbr_l);
	ret += ft_write_padding(info, ft_define_widthpad_l_nbr(info, nbr_l));
	if (info->left == FALSE)
		ret += ft_write_nbr(info, nbr, nbr_l);
	return (ret);
}
