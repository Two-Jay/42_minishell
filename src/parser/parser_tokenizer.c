/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:48:48 by jekim             #+#    #+#             */
/*   Updated: 2021/10/14 12:18:46 by jekim            ###   ########.fr       */
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

int tokenize_input(char *buf, t_data *data)
{
	(void)data;
	tri(get_split_buflen(buf, ' '));
	return (0);
}