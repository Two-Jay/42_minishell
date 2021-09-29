/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_addr_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 17:23:17 by jekim             #+#    #+#             */
/*   Updated: 2021/04/21 00:53:54 by jekim            ###   ########.fr       */
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

int	ft_write_addr(t_info *info, long long nbr, int nbr_l)
{
	int	ret;
	int	prcspad_l;
	int	base_l;

	ret = 0;
	prcspad_l = ft_define_prcspad_l_addr(info, nbr_l);
	base_l = 16;
	if (prcspad_l)
		ret += ft_write_prcspad(prcspad_l);
	ret += ft_write_addr_prefix();
	if (!(info->precision == 0 && nbr == 0))
		ft_putnbr(nbr, base_l, ft_define_base_arr(info));
	ret += nbr_l;
	return (ret);
}

int	ft_print_addr(t_info *info, va_list *ap)
{
	long long	addr;
	char		*base;
	int			ret;
	int			base_l;
	int			nbr_l;

	ret = 0;
	addr = ft_handle_addr_input(info, ap);
	base = ft_define_base_arr(info);
	base_l = 16;
	nbr_l = ft_intlen(addr, base_l, info);
	if (addr == 0 && info->precision == 0)
		return (ft_handle_null_addr(info, addr, nbr_l));
	if (info->left == TRUE)
		ret += ft_write_addr(info, addr, nbr_l);
	ret += ft_write_padding(info, ft_define_widthpad_l_addr(info, nbr_l));
	if (info->left == FALSE)
		ret += ft_write_addr(info, addr, nbr_l);
	return (ret);
}
