/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 01:39:48 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 01:42:23 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static char	*ft_call_parserset(char *fmt, t_info *info, va_list *ap)
{
	char	*origin;

	origin = fmt;
	fmt++;
	fmt = ft_check_flag(fmt, info);
	fmt = ft_check_width(fmt, info, ap);
	fmt = ft_check_precision(fmt, info, ap);
	fmt = ft_check_specifier(fmt, info);
	if (!fmt)
		return (origin);
	else
		return (fmt);
}

static void	ft_init_info(t_info *info)
{
	info->zeropad = FALSE;
	info->left = FALSE;
	info->only_dot = FALSE;
	info->input_negative = FALSE;
	info->precision_minus = FALSE;
	info->width = 0;
	info->precision = -1;
	info->type = 0;
	info->sign = 0;
}

static int	ft_printf_call_handler(t_info *info, va_list *ap)
{
	int	print_len;

	print_len = 0;
	if (info->type == 'c' || info->type == '%')
		print_len = ft_print_c(info, ap);
	if (info->type == 's')
		print_len = ft_print_s(info, ap);
	if (info->type == 'p')
		print_len = ft_print_addr(info, ap);
	if (info->type == 'd' || info->type == 'i' || info->type == 'u')
		print_len = ft_print_nbr(info, ap);
	if (info->type == 'x' || info->type == 'X')
		print_len = ft_print_nbr(info, ap);
	return (print_len);
}

static int	do_printf(char *fmt, va_list *ap)
{
	int		ret;
	t_info	info;

	ret = 0;
	while (*fmt)
	{
		if (*fmt != '%')
			ret += ft_putchar(*fmt);
		else if (*fmt == '%')
		{
			ft_init_info(&info);
			fmt = ft_call_parserset(fmt, &info, ap);
			ret += ft_printf_call_handler(&info, ap);
		}
		fmt++;
	}
	return (ret);
}

int	ft_printf(const char *fmt, ...)
{
	int		print_len;
	va_list	ap;
	t_info	*info;

	print_len = 0;
	va_start(ap, fmt);
	print_len = do_printf((char *)fmt, &ap);
	va_end(ap);
	return (print_len);
}
