/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 01:32:48 by jekim             #+#    #+#             */
/*   Updated: 2021/07/28 01:36:24 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft.h"

# define HEX_U "0123456789ABCDEF"
# define HEX_L "0123456789abcdef"
# define DEC "0123456789"
# define SPC_ARR "cspdiuxX%"
# define FLAG_ARR "0-+ "
# define FALSE 0
# define TRUE 1

typedef struct s_struct
{
	int			zeropad;
	int			left;
	int			only_dot;
	int			input_negative;
	int			precision_minus;
	int			width;
	int			precision;
	char		type;
	char		sign;
}				t_info;

int				ft_printf(const char *fmt, ...);

/*
** formatted string parser
*/
char			*ft_check_flag(char *fmt, t_info *info);
char			*ft_check_width(char *fmt, t_info *info, va_list *ap);
char			*ft_check_precision(char *fmt, t_info *info, va_list *ap);
char			*ft_check_specifier(char *fmt, t_info *info);

/*
** util functions
*/
char			*ft_define_base_arr(t_info *info);
int				ft_define_base_l(t_info *info);
int				ft_intlen(long long nbr, int base_l, t_info *info);
int				ft_getmax(int nbr1, int nbr2);
int				ft_getmin(int nbr1, int nbr2);
int				ft_write_padding(t_info *info, int pad_l);
int				ft_putchar(char c);
int				ft_handle_null_d(t_info *info);
void			ft_handle_info_exception(int *a);

/*
** diuxX specifier writer
*/
int				ft_print_nbr(t_info *info, va_list *ap);
int				ft_define_widthpad_l_nbr(t_info *info, int nbr_l);
int				ft_define_prcspad_l_nbr(t_info *info, int nbr_l);
long long		ft_handle_input(t_info *info, va_list *ap);

/*
** c% spcifier writer
*/
int				ft_print_c(t_info *info, va_list *ap);

/*
** s spcifier writer
*/
int				ft_print_s(t_info *info, va_list *ap);

/*
** p spcifier writer
*/
int				ft_print_addr(t_info *info, va_list *ap);
int				ft_write_addr_prefix(void);
int				ft_write_addr(t_info *info, long long nbr, int nbr_l);
int				ft_define_widthpad_l_addr(t_info *info, int nbr_l);
int				ft_define_prcspad_l_addr(t_info *info, int nbr_l);
long long		ft_handle_addr_input(t_info *info, va_list *ap);
int				ft_handle_null_addr(t_info *info, long long addr, int nbr_l);

#endif
