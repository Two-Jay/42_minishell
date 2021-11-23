/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_preprocess.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:05:39 by jekim             #+#    #+#             */
/*   Updated: 2021/11/23 15:14:18 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void is_spaced(const char *input, int input_idx, int *flag)
{
	int prflag;

	prflag = is_pipe_redirection(input, input_idx);
	if (prflag == 2)
	{
		;
	}
	if (prflag == 0)
	{
		;
	}
	else
		*flag = 0;
}

char *get_buf_considered(const char *input)
{
	int ix;
	int len;
	int qflag;
	int prdflag;
	char *ret;

	ix = 0;
	len = 0;
	while (input[ix])
	{
		is_quoted(input[ix], &qflag);
		prdflag = is_pipe_redirection(input, ix);
		if (!qflag && prdflag == 2)
		{
			len += 3;
			ix++;
		}
		if (!qflag && prdflag == 1)
			len += 2;
		len++;
		ix++;
	}
	ret = (char *)malloc(sizeof(char) * (len + 1));
	return (ret);
}

void insert_space(char *buf, char input, int *buf_idx, int *sflag)
{

	if (*sflag == 1)
	{
		buf[(*buf_idx)++] = ' ';
		buf[(*buf_idx)++] = input;				
	}
	if (*sflag == 2)
	{
		buf[(*buf_idx)++] = input;				
		buf[(*buf_idx)++] = ' ';
	}
	if (*sflag == 3)
	{
		buf[(*buf_idx)++] = ' ';
		buf[(*buf_idx)++] = input;
		buf[(*buf_idx)++] = ' ';
	}
}

char *preprocess_input(const char *input)
{
	int		ix;
	int		jx;
	int		sflag;
	int		qflag;
	char 	*buf;

	if (is_closed(input))
		return (NULL);
	ix = 0;
	jx = 0;
	qflag = 0;
	buf = get_buf_considered(input);
	while (input[ix])
	{
		is_inquote(input[ix], &qflag);
		is_spaced(input, ix, &sflag);
		if (sflag && !qflag)
			insert_space(buf, input[ix++], &jx, &sflag);
		else
			buf[jx++] = input[ix++];
	}
	buf[jx] = '\0';
	trs(buf);
	trp(buf);
	return (buf);
}
