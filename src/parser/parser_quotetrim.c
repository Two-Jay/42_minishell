/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotetrim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:06:36 by jekim             #+#    #+#             */
/*   Updated: 2021/12/03 14:36:41 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int  is_closer_single_qoute(const char *str, int ix, int flag)
{
	return (is_single_quote(str, ix) && flag == 1);
}

static int  is_closer_double_qoute(const char *str, int ix, int flag)
{
	return (is_double_quote(str, ix) && flag == 2);
}

char *search_endquote(char *str, int ix, int *flag)
{
	while (str[ix])
	{
		if (is_closer_single_qoute(str, ix, *flag)
			|| is_closer_double_qoute(str, ix, *flag))
			return (&(str[ix]));
		ix++;
	}
	if (flag)
		*flag = 0;
	return (NULL);
}

char *search_startquote(char *str, int ix, int *flag)
{
	while (str[ix])
	{
		if (is_single_qoute(str, ix) && *flag == 0)
		{
			*flag = 1;
			return (&(str[ix]));
		}
		if (is_double_qoute(str, ix) && *flag == 0)
		{
			*flag = 2;
			return (&(str[ix]));
		}
		ix++;
	}
	return (NULL);
}

char *cut_quotation_mark(char *str, char *startp, char *endp, int *ix)
{
	char	*ret;
	int		str_l;

	str_l = ft_strlen(str);
	ret = (char *)malloc(sizeof(char) * (str_l - 2));
	if (!ret)
		return (NULL);
	ft_strncpy(ret, startp, );
	return (ret);
}

void set_double_ptr(char **startp_ptr, char **endp_ptr)
{
	*startp_ptr = search_startquote(str, ix, &quote_flag);
	if (startp)
		*endp_ptr = search_endquote(str, ix, &quote_flag);	
}

int quote_trim(char *str, t_data *data)
{
	int     ix;
	int     quote_flag;
	char    *startp;
	char    *endp;
	char    *ret;

	ix = -1;
	quote_flag = 0;
	ret = str[ix];
	if (ft_strlen(str) >= 2)
	{
		while (str[++ix])
		{
			set_double_ptr(&startp, &endp);
			if (startp && endp)
			{
				ret = cut_quotation_mark(str, startp, endp, &ix);
				if (!ret)
					return (ERROR_OCCURED);
			}
		}
	}
	data->ip->qtrim_ret = ret;
	return (0);
}