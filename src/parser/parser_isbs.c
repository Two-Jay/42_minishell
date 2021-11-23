/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_isbs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:21:16 by jekim             #+#    #+#             */
/*   Updated: 2021/11/23 18:45:44 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int count_spclcmd_input(const char *str, int str_l)
{
	int ix;
	int ret;
	int check;
	int quote_flag;

	ret = 0;
	ix = 0;
	quote_flag = 0;
	while (str[ix])
	{
		is_inquoted(str, ix, &quote_flag);
		tri(str[ix]);
		tri(quote_flag);
		check = is_pipe_redirection(str, ix, str_l);
		if (!quote_flag && check)
		{
			if (check != 0)
				ret++;
			if (check == 2)
				ix++;
		}
		ix++;
	}
	return (ret);
}

static void cp_inserted_cmd1(char *dst, const char *str, int *ix, int *jx)
{
	dst[(*ix)++] = ' ';
	dst[(*ix)++] = str[(*jx)++];
	dst[(*ix)++] = ' ';
}

static void cp_inserted_cmd2(char *dst, const char *str, int *ix, int *jx)
{
	dst[(*ix)++] = ' ';
	dst[(*ix)++] = str[(*jx)++];
	dst[(*ix)++] = str[(*jx)++];
	dst[(*ix)++] = ' ';
}

static int do_insert_space(const char *str, t_data *data, int str_l)
{
	int ix;
	int jx;
	int check;
	int quote_flag;
	
	ix = 0;
	jx = 0;
	check = 0;
	quote_flag = 0;
	while (str[jx])
	{
		is_inquoted(str, jx, &quote_flag);
		check = is_pipe_redirection(str, jx, str_l);
		if (check == 0 || quote_flag)
			data->ip->isbs_ret[ix++] = str[jx++];
		else if (check == 1)
			cp_inserted_cmd1(data->ip->isbs_ret, str, &ix, &jx);
		else if (check == 2)
			cp_inserted_cmd2(data->ip->isbs_ret, str, &ix, &jx);
	}
	return (0);
}

int insert_space_beside_spclcmd(const char *str, t_data *data)
{
	int count_spclcmd;
	int str_l;

	(void)data;
	str_l = ft_strlen(str);
	count_spclcmd = count_spclcmd_input(str, str_l);
	if (count_spclcmd == 0)
		data->ip->isbs_ret = ft_strdup(str);
	else if (count_spclcmd)
	{
		data->ip->isbs_ret = (char *)malloc(sizeof(char) * (str_l + (count_spclcmd * 2) + 1));
		if (!data->ip->isbs_ret)
			return (ERROR_OCCURED);
		do_insert_space(str, data, str_l);
	}
	trs((char *)str);
	trp(data->ip->isbs_ret);
	trs(data->ip->isbs_ret);
	tri(count_spclcmd);
	return (0);
}