/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:54:24 by jekim             #+#    #+#             */
/*   Updated: 2021/11/26 02:00:49 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_end_quotation(const char *str, int ix, int flag)
 {
	return (is_quotation(str, ix) && flag == 0);
}

int check_split_condition(const char *str, int ix, int flag)
{
	if (is_end_quotation(str, ix, flag))
		return (TRUE);
	if (!ft_isspace(str[ix]) && ft_isspace(str[ix + 1]) && !flag)
		return (TRUE);
	if (!ft_isspace(str[ix]) && !str[ix + 1] && !flag)
		return (TRUE);
	return (FALSE);
}

int check_word_condition(const char *str, int ix, int flag)
{
	return (!flag && ft_isspace(str[ix]));
}

int get_word_l(const char *str)
{
	int l;
	int quote_flag;
	
	l = 0;
	quote_flag = 0;
	while (str[l])
	{
		is_inquoted(str, l, &quote_flag);
		if (check_word_condition(str, l, quote_flag))
			break ;
		l++;
	}
	return (l);
}

int	get_ret_l(const char *str)
{
	int ix;
	int ret;
	int quote_flag;

	ix = 0;
	ret = 0;
	quote_flag = 0;
	while (str[ix])
	{
		is_inquoted(str, ix, &quote_flag);
		if (check_split_condition(str, ix, quote_flag) == TRUE)
			ret++;
		ix++;
	}
	return (ret);
}

char **handle_error_free_ret(char **ret)
{
	int ix;
	
	ix = 0;
	while (ret[ix])
		free(ret[ix++]);
	free(ret);
	ret = NULL;
	return (NULL);
}

char **fill_split_ret(const char *str, int word_cnt, char **ret)
{
	int ix;
	int len;

	ix = 0;
	while (ix < word_cnt)
	{
		while (ft_isspace(*str))
			str++;
		len = get_word_l(str);
		ret[ix] = ft_strndup((char *)str, len);
		if (!ret[ix])
			return (handle_error_free_ret(ret));
		str += len;
		ix++;
	}
	return (ret);
}

int split_by_chunk(const char *str, t_data *data)
{
	int		ix;
	int		ret_l;

	ix = 0;
	ret_l = get_ret_l(str);
	data->ip->split_ret = (char **)malloc(sizeof(char *) * (ret_l + 1));
	if (!data->ip->split_ret)
		return (ERROR_OCCURED);
	data->ip->split_ret[ret_l] = NULL;
	data->ip->split_ret = fill_split_ret(str, ret_l, data->ip->split_ret);
	if (!data->ip->split_ret)
		return (ERROR_OCCURED);
	return (0);
}