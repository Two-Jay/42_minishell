/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:05:46 by jekim             #+#    #+#             */
/*   Updated: 2021/11/25 20:06:54 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parse_envkey_in_src(const char *src, int ix)
{
	char *ret;
	int ret_l;

	ret_l = 0;
	while (!ft_isspace(src[++ix]))
		ret_l++;
	ret = ft_strndup((char *)src + ix, ret_l);
	return (ret);
}

char	*search_and_copy_envval(const char *src, int ix, t_data *data)
{
	char *ret;
	char *parsed_envkey;

	parsed_envkey = parse_envkey_in_src(src, ix);
	ret = get_env(parsed_envkey, data);
	if (!ret)
	{
		free(parsed_envkey);
		return (NULL);
	}
	free(parsed_envkey);
	return (ret);
}

char	*append_env(char *src, int *now_ix, int src_l, t_data *data)
{
	char	*ret;
	char	*old_tmp;
	char	*envval_copied;
	int		envval_l;
	int		ix;

	ix = -1;
	old_tmp = src;
	trs(src);
	tri(*now_ix);
	tri(src_l);
	envval_copied = search_and_copy_envval(src, *now_ix, data);
	envval_l = ft_strlen(envval_copied);
	ret = (char *)ft_calloc(sizeof(char), src_l + envval_l + 1);
	if (!ret)
		return (NULL);
	ret[src_l + envval_l] = '\0';
	ft_strncpy(ret, src, *now_ix);
	if (envval_copied)
		ft_strncpy(ret + *now_ix, envval_copied, envval_l);
	ft_strncpy(ret + *now_ix + envval_l, src + *now_ix, src_l - *now_ix);
	*now_ix += envval_l;
	free(envval_copied);
	free(old_tmp);
	return (ret);
}

char	*append_errono(char *src, int *current_idx, int buf_l)
{
	char	*ret;
	char	*old_tmp;
	char	*errno_str;
	int		errno_l;
	int		ix;

	ix = -1;
	old_tmp = src;
	errno_str = ft_itoa(errno);
	errno_l = ft_strlen(errno_str);
	ret = (char *)ft_calloc(sizeof(char), buf_l + errno_l + 1);
	if (!ret)
		return (NULL);
	ret[buf_l + errno_l] = '\0';
	ft_strncpy(ret, src, *current_idx + 1);
	ft_strncpy(ret + *current_idx, errno_str, errno_l + 1);
	ft_strncpy(ret + *current_idx + errno_l,
		src + *current_idx, buf_l - *current_idx);
	*current_idx += errno_l;
	free(errno_str);
	free(old_tmp);
	return (ret);
}

int is_envflag(const char *str, int ix, int flag)
{
	return (str[ix] == '$' && flag != 1);
}

int is_errnoflag(const char *str, int ix, int flag)
{
	return (str[ix] == '$' &&  str[ix + 1] == '?' && flag != 1);
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
		if (is_errnoflag(str, ix, quote_flag) || is_envflag(str, ix, quote_flag))
			ret++;
	}
	if (ret > 0)
		return (TRUE);
	return (FALSE);
}

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
			is_inquoted(str, ix, &quote_flag);
			trc(dst[ix]);
			// if (is_errnoflag(str, ix, quote_flag))
			// 	dst = append_errono(dst, &ix, ft_strlen(dst));
			if (is_envflag(str, ix, quote_flag))
				dst = append_env(dst, &ix, ft_strlen(dst), data);
		}
	}
	data->ip->scenv_ret = dst;
	return (0);
}