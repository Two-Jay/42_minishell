/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:05:46 by jekim             #+#    #+#             */
/*   Updated: 2021/12/06 10:31:35 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
** env part
*/

int is_end_envkey(const char *src, int ix)
{
	return ((ft_isspace(src[ix])
			|| is_double_quote(src, ix)
			|| is_single_quote(src, ix))
			|| src[ix] == '$');
}

int get_envkey_l(const char *src, int ix)
{
	int ret;

	ret = 0;
	while (src[ix])
	{
		if (is_end_envkey(src, ix))
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
int search_and_copy_envval(const char *src, t_eb *eb, t_data *data)
{
	eb->key_l = get_envkey_l(src, eb->now_ix + 1);
	eb->envkey = ft_strndup((char *)(src + eb->now_ix + 1), eb->key_l);
	eb->envval = get_env(eb->envkey, data);
	eb->value_l = ft_strlen(eb->envval);
	return (0);
}

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

char	*return_append_env(t_eb	*eb, char *ret)
{
	if (eb->srcp)
		free(eb->srcp);
	if (eb->envkey)
		free(eb->envkey);
	if (eb->envval)
		free(eb->envval);
	if (eb->errno_str)
		free(eb->errno_str);
	if (eb)
		free(eb);
	return (ret);
}

char	*fetch_env_in_src(t_eb *eb)
{
	char *ret;

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

/*
** errno part
*/
int search_and_copy_dq(t_eb *eb, t_data *data)
{
	eb->errno_str = ft_itoa(data->dq);
	eb->errno_l = ft_strlen(eb->errno_str);
	return (0);
}

char	*fetch_dq_in_src(t_eb *eb)
{
	char *ret;

	ret = (char *)ft_calloc(sizeof(char), eb->src_l + eb->errno_l + 1);
	if (!ret)
		return (NULL);
	ft_strncpy(ret, eb->srcp, eb->now_ix);
	ft_strncpy(ret + eb->now_ix, eb->errno_str, eb->errno_l);
	ft_strncpy(ret + eb->now_ix + eb->errno_l,
		eb->srcp + eb->now_ix + eb->errno_l + 1,
		eb->src_l - eb->now_ix - 1);
	ret[eb->src_l + eb->errno_l] = '\0';
	return (ret);
}

char	*append_dq(char *src, int *now_ix, t_data *data)
{
	char	*ret;
	t_eb	*envbucket;

	envbucket = set_envbucket(src, *now_ix);
	if (!envbucket
		|| search_and_copy_dq(envbucket, data))
		return (return_append_env(envbucket, NULL));
	ret = fetch_dq_in_src(envbucket);
	if (!ret)
		return (return_append_env(envbucket, NULL));
	*now_ix += envbucket->errno_l - 1;
	return (return_append_env(envbucket, ret));
}

/*
** envflag ($) checker
*/

int is_envflag(const char *str, int ix, int flag)
{
	return (str[ix] == '$' && flag != 1);
}

int is_dq(const char *str, int ix, int flag)
{
	return (str[ix] == '$' && str[ix + 1] == '?' && flag != 1);
}

int check_envcnt(const char *str)
{
	int ix;
	int ret;
	int quote_flag;

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

/*
** main env parsing function
*/
int setup_and_check_env(const char *str, t_data *data)
{
	int ix;
	char *dst;
	int quote_flag;

	ix = -1;
	quote_flag = 0;
	dst = ft_strdup(str);
	if (check_envcnt(dst) == TRUE)
	{
		while (dst[++ix])
		{
			is_inquoted(dst, ix, &quote_flag);
			if (is_dq(dst, ix, quote_flag))
				dst = append_dq(dst, &ix, data);
			else if (is_envflag(dst, ix, quote_flag))
				dst = append_env(dst, &ix, data);
		}
	}
	data->ip->scenv_ret = dst;
	return (0);
}