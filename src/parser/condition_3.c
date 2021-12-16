/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:56:33 by jekim             #+#    #+#             */
/*   Updated: 2021/12/16 13:57:52 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_filepath(t_token *token)
{
	return (is_redirection(token->prev->content, 0));
}

int	is_quoted_input(char *str)
{
	int	ix;
	int	cnt_dq;
	int	cnt_sq;

	ix = -1;
	cnt_dq = 0;
	cnt_sq = 0;
	while (str[++ix])
	{
		if (is_single_quote(str, ix))
			cnt_sq++;
		if (is_double_quote(str, ix))
			cnt_dq++;
	}
	if (cnt_dq / 2 > 0 || cnt_sq / 2 > 0)
		return (TRUE);
	return (FALSE);
}

int	is_end_quotation(const char *str, int ix, int flag)
{
	return (is_quotation(str, ix) && flag == 0);
}

int	is_word_condition(const char *str, int ix, int flag)
{
	return (!flag && ft_isspace(str[ix]));
}

int	check_split_condition(const char *str, int ix, int flag)
{
	if (is_end_quotation(str, ix, flag))
		return (TRUE);
	if (!ft_isspace(str[ix]) && ft_isspace(str[ix + 1]) && !flag)
		return (TRUE);
	if (!ft_isspace(str[ix]) && !str[ix + 1] && !flag)
		return (TRUE);
	return (FALSE);
}
