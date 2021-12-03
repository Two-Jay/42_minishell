/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotetrim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:06:36 by jekim             #+#    #+#             */
/*   Updated: 2021/12/03 22:40:17 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_quoted_input(char *str)
{
	int ix;
	int cnt_dq;
	int cnt_sq;

	ix = -1;
	cnt_dq = 0;
	cnt_sq = 0;
	while (str[++ix])
	{
		if (is_single_quote(str, ix))
			cnt_sq++;
		if (is_double_quote(str, ix))
			cnt_dq++;
	}
	if (cnt_dq / 2 > 0 || cnt_sq / 2 > 0)
		return (TRUE);
	return (FALSE);
}

int set_converted_into_data(char *ret, t_data *data)
{
	data->ip->qtrim_ret = ret;
	return (0);
}

char *flag_clicker(char *ret, int ix, int *flag, int base)
{
	if (*flag == base)
		*flag = 0;
	else if (*flag == 0)
		*flag = base;
	if (*flag == base || *flag == 0)
		return (ret + ix);
}

char *search_quote(char *ret, int *flag)
{
	int ix;
	int flag;

	ix = -1;
	flag = 0;
	while (ret[++ix])
	{
		if (is_single_quote(ret, ix))
			return (flag_clicker(ret, ix, flag, 1));
		if (is_double_quote(ret, ix))
			return (flag_clicker(ret, ix, flag, 2));
	}
	return (NULL);
}

int quote_trim(char *str, t_data *data)
{
	char 	*ret;
	char	*searchbase_p;
	int		quote_flag;

	quote_flag = 0;
	ret = ft_strdup(str);
	searchbase_p = ret;
	if (is_quoted_input(ret) == TRUE)
		return (set_converted_into_data(ret, data));
	searchbase_p = search_quote(searchbase_p, quote_flag);
	return (set_converted_into_data(ret, data));
}
