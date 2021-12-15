/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:11:11 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 17:35:40 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_envflag(const char *str, int ix, int flag)
{
	return (str[ix] == '$' && flag != 1);
}

int	is_dq(const char *str, int ix, int flag)
{
	return (str[ix] == '$' && str[ix + 1] == '?' && flag != 1);
}

int	is_env_print_process(const char *str, int ix, int flag)
{
	return (str[ix] == '$' && str[ix + 1] == '$' && flag != 1);
}

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
