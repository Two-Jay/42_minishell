/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotetrim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:06:36 by jekim             #+#    #+#             */
/*   Updated: 2021/12/04 14:26:37 by jekim            ###   ########.fr       */
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

int set_converted_into_data(char *str, char *ret, t_data *data, int errflag)
{
	if (errflag)
		data->ip->qtrim_ret = ft_strdup(str);
	else
		data->ip->qtrim_checker = ret;
	return (0);
}

int set_int_checker(t_data *data, int length)
{
	int ix;
	
	ix = -1;
	data->ip->qtrim_checker = (int *)malloc(length * sizeof(int));
	if (!data->ip->qtrim_checker)
		return (ERROR_OCCURED);
	data->ip->qtrim_checker[length] = '\0';
	while (data->ip->qtrim_checker[++ix])
		data->ip->qtrim_checker[ix] = 1;
	return (0);
}

int check_opener_quote(char *ret, int ix, int *qf, t_data *data)
{
	while (ret[ix])
	{
		if (is_single_quote(ret, ix)
			&& *qf == 0)
		{
			*qf = 1;
			break ;
		}
		if (is_double_quote(ret, ix)
			&& *qf == 0)
		{
			*qf = 2;
			break ;
		}
		ix++;
	}
	return (ix);
}

int check_closer_quote(char *ret, int ix, int *qf, t_data *data)
{
	while (ret[ix])
	{
		if (is_single_quote(ret, ix)
			&& *qf == 1)
		{
			*qf = 0;
			break ;
		}
		if (is_double_quote(ret, ix)
			&& *qf == 2)
		{
			*qf = 0;
			break ;
		}
		ix++;
	}
	return (ix);
}

void check_index_into_checker_array(t_data *data, int startp, int endp)
{
	data->ip->qtrim_checker[startp] = 0;
	data->ip->qtrim_checker[endp] = 0;
}

int check_unprint_char(char *ret, t_data *data)
{
	int		startp;
	int		endp;
	int		ix;
	int		quote_flag;

	ix = -1;
	quote_flag = 0;
	while (ret[++ix])
	{
		startp = -1;
		endp = -1;
		startp = checker_opener_quote(ret, &ix, &quote_flag, data);
		endp = checker_closer_quote(ret, &ix, &quote_flag, data);
		if (startp > -1 || endp > -1)
			check_index_into_checker_array(data, startp, endp);
		if (endp > -1)
			ix = endp;
	}
	return (0);
}

int get_ret_buf_length(t_data *data)
{
	int ret;
	int ix;
	
	ret = 0;
	ix = -1;
	while (data->ip->qtrim_checker[++ix])
	{
		if (data->ip->qtrim_checker[ix] == 1)
			ret++;
	}
	return (ret);
}

void copy_as_checked(char *condition, char *str, char *ret)
{
	int	ix;
	int jx;


	ix = 0;
	jx = 0;
	while (str[ix])
	{
		if (condition[ix] == 1)
			ret[jx++] = str[ix];
		ix++;
	}
}

int strdup_as_checked(char *str, t_data *data)
{
	char	*ret;
	int		len;
	int		ix;

	len = get_ret_buf_length(data);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (ERROR_OCCURED);
	copy_as_checked(data->ip->qtrim_checker, str, ret);
	return (0);
}

int quote_trim(char *str, t_data *data)
{
	char 	*ret;


	if (is_quoted_input(ret) == FALSE)
		return (set_converted_into_data(str, NULL ,data, 1));
	if (set_int_checker(data, ft_strlen(ret))
		|| check_unprint_char(str, data)
		|| strdup_as_checked(ret, data))
		return (ERROR_OCCURED);
	return (set_converted_into_data(str, ret, data, 0));
}
