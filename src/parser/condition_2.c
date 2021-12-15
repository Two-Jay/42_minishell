/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:55:29 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 17:33:25 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_start_charset_envkey(char c)
{
	return (ft_isalpha(c) || c == '_');
}

int	is_end_envkey(const char *src, int ix)
{
	if (ix == 0 && !is_start_charset_envkey(src[ix]))
		return (TRUE);
	if (!ft_isalnum(src[ix]) && src[ix] != '_')
		return (TRUE);
	return (FALSE);
}

int	is_CMD(int cmd_flag)
{
	return (cmd_flag == 0);
}

int	is_contain_space_or_dash(t_token *token)
{
	int	ix;

	ix = 0;
	while (token->content[ix])
	{
		if (ft_isspace(token->content[ix]))
			return (TRUE);
		if (ix > 0 && token->content[ix] == '-')
			return (TRUE);
		ix++;
	}
	return (FALSE);
}

int	is_flag(t_token *token)
{
	return (token->prev->type == CMD
		&& token->content[0] == '-'
		&& ft_strlen(token->content) > 1
		&& is_contain_space_or_dash(token) == FALSE);
}
