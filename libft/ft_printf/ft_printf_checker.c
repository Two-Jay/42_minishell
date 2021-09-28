/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 13:16:09 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 02:44:02 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_printf.h"

char	*ft_check_flag(char *fmt, t_info *info)
{
	while (ft_strchr(FLAG_ARR, *fmt))
	{
		if (*fmt == '0')
			info->zeropad = TRUE;
		else if (*fmt == '-')
		{
			info->left = TRUE;
		}
		fmt++;
	}
	if (info->left == 1 && info->zeropad == 1)
		info->zeropad = 0;
	return (fmt);
}

char	*ft_check_width(char *fmt, t_info *info, va_list *ap)
{
	int	param;

	if (*fmt == '*')
	{
		param = va_arg(*ap, int);
		if (param < 0)
		{
			param *= -1;
			info->left = TRUE;
			if (info->zeropad == TRUE)
				info->zeropad = FALSE;
		}
		info->width = param;
		fmt++;
	}
	else if (*fmt >= '1' && *fmt <= '9')
	{
		while (*fmt >= '0' && *fmt <= '9')
		{
			info->width *= 10;
			info->width += (*(fmt++) - '0');
		}
	}
	return (fmt);
}

static void	ft_prcs_asterisk_precision(t_info *info, va_list *ap)
{
	info->precision = va_arg(*ap, int);
	if (info->precision < 0)
		info->precision = -1;
}

char	*ft_check_precision(char *fmt, t_info *info, va_list *ap)
{
	if (*fmt == '.')
	{
		fmt++;
		info->precision = 0;
		if (*fmt == '*')
		{
			ft_prcs_asterisk_precision(info, ap);
			fmt++;
		}
		else if (*fmt >= '0' && *fmt <= '9')
		{
			while (*fmt >= '0' && *fmt <= '9')
				info->precision = (info->precision * 10) + ((*fmt++) - '0');
		}
		else
			info->only_dot = TRUE;
	}
	return (fmt);
}

char	*ft_check_specifier(char *fmt, t_info *info)
{
	if (ft_strchr(SPC_ARR, *fmt))
	{
		info->type = *fmt;
		return (fmt);
	}
	else
		return (NULL);
}
