/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:54:24 by jekim             #+#    #+#             */
/*   Updated: 2021/11/23 15:09:58 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void check_isquoted(const char *str, int *flag)
{
	if (*str == 34)
	{
		if (*flag == 2)
			*flag == 0;
		if (*flag == 0)
			*flag == 2;
	}
	if (*str == 39)
	{
		if (*flag == 1)
			*flag == 0;
		if (*flag == 0)
			*flag == 1;	
	}
}

int find_split_point(const char *str, char **startp, char **endp)
{
	int ix;
	int quote_flag;
	int limit;

	ix = 0;
	quote_flag = 0;
	limit = ft_strlen(str);
	if (limit == 0)
		return (ERROR_OCCURED);
	while (ft_isspace(str[ix]))
		ix++;
	*startp = str + ix;
	limit = ft_strlen(*startp);
	while (ix < limit)
	{
		check_isquoted(*startp + ix, &quote_flag);
		if (!quote_flag && ft_isspace(*startp + ix))\
			break ;
		ix++;
	}
	*endp = *startp + ix;
	return (0);
}

int	get_ret_l(const char *str)
{
	int ix;
	int ret;
	int quote_flag;

	ix = 0;
	quote_flag = 0;
	while (str[ix])
	{
		
		if ()
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