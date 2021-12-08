/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotetrim.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:06:36 by jekim             #+#    #+#             */
/*   Updated: 2021/12/08 11:53:48 by jekim            ###   ########.fr       */
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

int handle_error(char *str, char *dst)
{
	dst = ft_strdup(str);
	return (0);
}

int set_int_checker(t_data *data, int length)
{
	int ix;
	
	ix = -1;
	data->ip->qtrim_checker = (int *)ft_calloc((length + 1), sizeof(int));
	if (!data->ip->qtrim_checker)
		return (ERROR_OCCURED);
	return (0);
}

int check_opener_quote(char *ret, int ix, int *qf)
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

int check_closer_quote(char *ret, int ix, int *qf)
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

void check_into_checker_arr(int *arr, int startp, int endp)
{
	arr[startp] = 1;
	arr[endp] = 1;
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
		startp = check_opener_quote(ret, ix, &quote_flag);
		endp = check_closer_quote(ret, startp + 1, &quote_flag);
		if (startp > -1 || endp > -1)
			check_into_checker_arr(data->ip->qtrim_checker,startp, endp);
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
		if (data->ip->qtrim_checker[ix] == 0)
			ret++;
	}
	return (ret);
}

char *strdup_as_checked(char *str, t_data *data)
{
	char	*ret;
	int		len;
	int		ix;
	int		jx;

	ix = 0;
	jx = 0;
	len = get_ret_buf_length(data);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	ret[len] = '\0';
	while (str[ix])
	{
		if (data->ip->qtrim_checker[ix] == 0)
			ret[jx++] = str[ix];
		ix++;
	}
	return (ret);
}

char *free_checker(t_data *data)
{
	if (data->ip->qtrim_checker)
		free(data->ip->qtrim_checker);
	return (NULL);
}

char *quote_trim(char *str, t_data *data)
{
	char *ret;

	if (is_quoted_input(str) == FALSE)
		return (str);
	if (set_int_checker(data, ft_strlen(str)))
		return (NULL);
	check_unprint_char(str, data);
	ret = strdup_as_checked(str, data);
	if (!ret)
		return (free_checker(data), NULL);
	return (free_checker(data), ret);
}
