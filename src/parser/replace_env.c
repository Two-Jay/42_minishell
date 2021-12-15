/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:05:46 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 18:17:20 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_eb	*set_envbucket(char *src, int now_ix)
{
	t_eb	*ret;

	ret = (t_eb *)ft_calloc(sizeof(t_eb), 1);
	if (!ret)
		return (NULL);
	ret->now_ix = now_ix;
	ret->srcp = src;
	ret->src_l = ft_strlen(src);
	return (ret);
}

int	save_target(t_eb *eb, int target)
{
	eb->nbr_str = ft_itoa(target);
	eb->nbr_l = ft_strlen(eb->nbr_str);
	return (0);
}

int	check_envcnt(const char *str)
{
	int	ix;
	int	ret;
	int	quote_flag;

	ix = -1;
	ret = 0;
	quote_flag = 0;
	while (str[++ix])
	{
		is_inquoted(str, ix, &quote_flag);
		if (is_dq(str, ix, quote_flag) || is_envflag(str, ix, quote_flag))
			ret++;
	}
	if (ret > 0)
		return (TRUE);
	return (FALSE);
}

int	setup_and_check_env(const char *str, t_data *data)
{
	int		ix;
	char	*dst;
	int		quote_flag;

	ix = -1;
	quote_flag = 0;
	dst = ft_strdup(str);
	if (check_envcnt(dst) == TRUE)
	{
		while (dst[++ix])
		{
			is_inquoted(dst, ix, &quote_flag);
			if (is_dq(dst, ix, quote_flag))
				dst = append_nbr(dst, &ix, g_dq);
			else if (is_env_print_process(dst, ix, quote_flag))
				dst = append_nbr(dst, &ix, getpid());
			else if (is_envflag(dst, ix, quote_flag)
				&& is_start_charset_envkey(dst[ix + 1]))
				dst = append_env(dst, &ix, data);
		}
	}
	data->ip->scenv_ret = dst;
	return (0);
}
