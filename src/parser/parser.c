/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 09:05:39 by jekim             #+#    #+#             */
/*   Updated: 2021/10/07 04:50:14 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_closed(const char *input)
{
	int	ix;
	int	squote_cnt;
	int	dquote_cnt;

	squote_cnt = 0;
	dquote_cnt = 0;
	ix = 0;
	while (input[ix])
	{
		if (input[ix] == '\"')
			dquote_cnt++;
		if (input[ix] == '\'')
			squote_cnt++;
		ix++;
	}
	if (dquote_cnt % 2 == 0 && squote_cnt % 2 == 0)
		return (0);
	return (1);
}

int	preprocess_quote(const char *input)
{
	if (is_closed(input))
		return (1);
	return (0);
}

int	parse_input(const char *input)
{
	printf("%s\n%d\n", input, is_closed(input));
	return (0);
}