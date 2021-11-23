/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:54:24 by jekim             #+#    #+#             */
/*   Updated: 2021/11/24 08:39:24 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		if (!quote_flag
			&& (!ft_isspace(str[ix])
			&& (ft_isspace(str[ix + 1]) || str[ix + 1] == '\0')))
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