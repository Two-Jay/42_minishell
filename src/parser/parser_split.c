/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:54:24 by jekim             #+#    #+#             */
/*   Updated: 2021/11/23 17:40:50 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_ret_l(const char *str)
{
	int ix;
	int ret;
	int quote_flag;

	ix = 0;
	quote_flag = 0;
	while (str[ix])
	{
		is_inquoted(str[ix], )
		if (!quote_flag
			&& (str[ix] && (str[ix + 1] == ' ' || str[ix + 1] == NULL)))
		ix++;
	}
}

int split_by_chunk(const char *str, t_data *data)
{
	int		ix;
	int		ret_l;
	char	**ret;

	ix = 0;
	ret_l = get_ret_l(str);
}