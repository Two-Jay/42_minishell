/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:54:24 by jekim             #+#    #+#             */
/*   Updated: 2021/12/16 13:59:12 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_word_l(const char *str)
{
	int	l;
	int	quote_flag;

	l = 0;
	quote_flag = 0;
	while (str[l])
	{
		is_inquoted(str, l, &quote_flag);
		if (is_word_condition(str, l, quote_flag))
			break ;
		l++;
	}
	return (l);
}

int	get_ret_l(const char *str)
{
	int	ix;
	int	ret;
	int	quote_flag;

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

char	**handle_error_free_ret(char **ret)
{
	int	ix;

	ix = 0;
	while (ret[ix])
		free(ret[ix++]);
	free(ret);
	ret = NULL;
	return (NULL);
}

char	**fill_split_ret(const char *str, int word_cnt, char **ret)
{
	int	ix;
	int	len;

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

int	split_by_chunk(const char *str, t_data *data)
{
	int	ix;
	int	ret_l;

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
