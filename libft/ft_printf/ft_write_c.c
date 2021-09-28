/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 04:45:11 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:47:24 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static int	ft_define_c_target(t_info *info, va_list *ap)
{
	if (info->type == '%')
		return ('%');
	else
		return ((char)va_arg(*ap, int));
}

static int	ft_define_c_len(t_info *info)
{
	if (info->width > 1)
		return (info->width);
	else
		return (1);
}

int	ft_print_c(t_info *info, va_list *ap)
{
	char	target;
	int		pad_len;
	int		ret;

	pad_len = ft_define_c_len(info) - 1;
	target = ft_define_c_target(info, ap);
	ret = 0;
	if (info->left == 1)
		ret += ft_putchar(target);
	ret += ft_write_padding(info, pad_len);
	if (info->left == 0)
		ret += ft_putchar(target);
	return (ret);
}
