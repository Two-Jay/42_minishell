/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:48:48 by jekim             #+#    #+#             */
/*   Updated: 2021/10/14 20:21:05 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_split_buflen(char *buf, char c)
{
	int ix;
	int qflag;
	int ret;

	ix = 0;
	qflag = 0;
	ret = 0;
	while (buf[ix])
	{
		is_inquote(buf[ix], &qflag);
		if (buf[ix] != c
			&& (buf[ix + 1] == c || !buf[ix + 1])
			&& !qflag)
			ret++;
		ix++;
	}
	return (ret);
}

char *get_splited_tokenstr(char *buf)
{
	
}

int tokenize_input(char **ret, char *buf, t_data *data)
{
	char	**ret;
	int		ix;
	int		ret_len;
	
	ix = 0;
	ret_len = get_split_buflen(buf, ' ');
	ret = (char **)malloc(sizeof(char *) * (ret_len + 1));
	while (ix < ret_len)
	{
		ret[ix] = get_splited_tokenstr(buf, &idx)
		ix++;
	}
	return (0);
}