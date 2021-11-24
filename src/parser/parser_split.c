/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:54:24 by jekim             #+#    #+#             */
/*   Updated: 2021/11/24 14:43:45 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_start_quotation(const char *str, int ix)
{
	return (is_quotation(&str[ix]) && (ix == 0|| ft_isspace(str[ix - 1])));
}

int is_start_string_out_of_quotation(const char *str, int ix, int flag)
{
	return (!flag && ft_isspace(str[ix - 1]) && !ft_isspace(str[ix]));
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
		if (is_start_quotation(str, ix))
			ret++;
		if (!ft_isspace(str[ix]) && ft_isspace(str[ix + 1]) && !quote_flag)
			ret++;
		if (!ft_isspace(str[ix]) && !str[ix + 1] && !quote_flag)
			ret++;
		ix++;
	}
	return (ret);
}

int split_by_chunk(const char *str, t_data *data)
{
	int		ix;
	int		ret_l;
	char	**ret;

	ix = 0;
	(void)data;
	ret_l = get_ret_l(str);
	ret = (char **)malloc(sizeof(char *) * (ret_l + 1));
	if (!ret)
		return (ERROR_OCCURED);
	tri(ret_l);
	return (0);
}