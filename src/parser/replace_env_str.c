/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 17:07:15 by jekim             #+#    #+#             */
/*   Updated: 2021/12/16 00:04:02 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	get_envkey_l(const char *src, int ix)
{
	int	ret;

	ret = 0;
	while (src[ix])
	{
		if (is_end_envkey(src, ix) == TRUE)
			break ;
		ix++;
		ret++;
	}
	return (ret);
}

/*
** do not care here about get_env() returns NULL;
** when get_env() returns NULL, it means that the value was not found
*/
int	search_and_copy_envval(const char *src, t_eb *eb, t_data *data)
{
	eb->key_l = get_envkey_l(src, eb->now_ix + 1);
	eb->envkey = ft_strndup((char *)(src + eb->now_ix + 1), eb->key_l);
	eb->envval = get_env(eb->envkey, data);
	eb->value_l = ft_strlen(eb->envval);
	return (0);
}

char	*fetch_env_in_src(t_eb *eb)
{
	char	*ret;

	ret = (char *)ft_calloc(sizeof(char), eb->src_l + eb->value_l + 1);
	if (!ret)
		return (NULL);
	ft_strncpy(ret, eb->srcp, eb->now_ix);
	if (eb->envval)
	{
		ft_strncpy(ret + eb->now_ix, eb->envval, eb->value_l);
		ft_strncpy(ret + eb->now_ix + eb->value_l,
			eb->srcp + eb->now_ix + eb->key_l + 1,
			eb->src_l - eb->now_ix - eb->key_l);
	}
	else
	{
		eb->value_l = 0;
		ft_strncpy(ret + eb->now_ix,
			eb->srcp + eb->now_ix + eb->key_l + 1,
			eb->src_l - eb->now_ix - eb->key_l);
	}
	ret[eb->src_l + eb->value_l] = '\0';
	return (ret);
}

char	*append_env(char *src, int *now_ix, t_data *data)
{
	char	*ret;
	t_eb	*envbucket;

	envbucket = set_envbucket(src, *now_ix);
	if (!envbucket
		|| search_and_copy_envval(src, envbucket, data))
		return (return_append_env(envbucket, NULL));
	ret = fetch_env_in_src(envbucket);
	if (!ret)
		return (return_append_env(envbucket, NULL));
	*now_ix += envbucket->value_l - 1;
	return (return_append_env(envbucket, ret));
}
