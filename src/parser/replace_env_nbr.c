/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_nbr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:02:22 by jekim             #+#    #+#             */
/*   Updated: 2021/12/15 18:17:16 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*fetch_nbr_in_src(t_eb *eb)
{
	char	*ret;
	char	*remain_startp;
	int		remain_l;

	ret = (char *)ft_calloc(sizeof(char), eb->src_l + eb->nbr_l + 1);
	if (!ret)
		return (NULL);
	ft_strncpy(ret, eb->srcp, eb->now_ix);
	ft_strncpy(ret + eb->now_ix, eb->nbr_str, eb->nbr_l);
	remain_startp = eb->srcp + eb->now_ix + 2;
	remain_l = eb->src_l - eb->now_ix - 1;
	ft_strncpy(ret + eb->now_ix + eb->nbr_l, remain_startp, remain_l);
	ret[eb->src_l + eb->nbr_l] = '\0';
	return (ret);
}

char	*return_append_env(t_eb	*eb, char *ret)
{
	if (eb->srcp)
		free(eb->srcp);
	if (eb->envkey)
		free(eb->envkey);
	if (eb->envval)
		free(eb->envval);
	if (eb->nbr_str)
		free(eb->nbr_str);
	if (eb)
		free(eb);
	return (ret);
}

char	*append_nbr(char *src, int *now_ix, int target)
{
	char	*ret;
	t_eb	*envbucket;

	envbucket = set_envbucket(src, *now_ix);
	if (!envbucket
		|| save_target(envbucket, target))
		return (return_append_env(envbucket, NULL));
	ret = fetch_nbr_in_src(envbucket);
	if (!ret)
		return (return_append_env(envbucket, NULL));
	*now_ix += 2;
	return (return_append_env(envbucket, ret));
}
