/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 16:15:54 by jekim             #+#    #+#             */
/*   Updated: 2021/12/11 00:33:21 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

static char	*ft_define_target_s(va_list *ap)
{
	char	*target;

	target = va_arg(*ap, char *);
	if (!target)
		target = "(null)";
	return (target);
}

static int	ft_define_widthpad_l_s(t_info *info, int print_l)
{
	int		ret;

	ret = 0;
	if (info->width > 0 && info->width > print_l)
		ret = info->width - print_l;
	if (info->only_dot == TRUE || info->precision == 0)
		ret = info->width;
	if (ret < 0)
		return (0);
	return (ret);
}

static int	ft_define_print_l_s(t_info *info, int str_l)
{
	int		ret;

	ret = str_l;
	if (info->precision >= 0 && info->precision < str_l)
		ret = info->precision;
	if (info->only_dot == TRUE)
		ret = 0;
	if (ret < 0)
		return (0);
	return (ret);
}

static int	ft_write_str(char *target, int print_l)
{
	char	*buf;
	int		ix;

	buf = (char *)malloc(sizeof(char) * (print_l + 1));
	if (!buf)
		return (0);
	buf[print_l + 1] = '\0';
	ix = 0;
	while (ix < print_l)
	{
		buf[ix] = target[ix];
		ix++;
	}
	write(1, buf, print_l);
	free(buf);
	return (print_l - 1);
}

int	ft_print_s(t_info *info, va_list *ap)
{
	int		ret;
	int		print_l;
	int		pad_l;
	int		str_l;
	char	*target;

	ret = 0;
	target = ft_define_target_s(ap);
	str_l = ft_strlen(target);
	print_l = ft_define_print_l_s(info, str_l);
	pad_l = ft_define_widthpad_l_s(info, print_l);
	if (info->left == TRUE)
		ret += ft_write_str(target, print_l);
	ret += ft_write_padding(info, pad_l);
	if (info->left == FALSE)
		ret += ft_write_str(target, print_l);
	return (ret);
}
