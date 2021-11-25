/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:05:46 by jekim             #+#    #+#             */
/*   Updated: 2021/11/25 14:38:05 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parse_envkey_in_src(const char *src, int ix)
{
	char *ret;

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

char	*append_env(char *src, int *current_idx, int src_l, t_data *data)
{
	char	*ret;
	char	*old_tmp;
	char	*envval_copied;
	int		envval_l;
	int		ix;

	ix = -1;
	envval_copied = search_and_copy_envval(src, *current_idx, data);
	envval_l = ft_strlen(envval_copied);
	ret = (char *)ft_calloc(sizeof(char), src_l + envval_l + 1);
	if (!ret)
		return (ERROR_OCCURED);
	ret[src_l + envval_l] = '\0';
	ft_strncpy(ret, src, current_idx);
	ft_strncpy(ret + *current_idx, envval_copied, envval_l);
	ft_strncpy(ret + *current_idx + envval_l,
		src + *current_idx, src_l - *current_idx);
	*current_idx += envval_l;
	free(*envval_copied);
	free(old_tmp);
	return (ret);
}

int append_errono(char *src, int *current_idx, int buf_l)
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
		return (ERROR_OCCURED);
	ret[buf_l + errno_l] = '\0';
	ft_strncpy(ret, src, *current_idx + 1);
	ft_strncpy(ret + *current_idx, errno_str, errno_l + 1);
	ft_strncpy(ret + *current_idx + errno_l,
		src + *current_idx, buf_l - *current_idx);
	*current_idx += errno_l;
	free(errno_str);
	free(old_tmp);
	src = ret;
	return (0);
}

int is_envflag(const char *str, int ix, int flag)
{
	return (str[ix] == '$' && flag != 1);
}

int is_errnoflag(const char *str, int ix, int flag)
{
	return (str[ix] == '$' &&  str[ix + 1] == '?' && flag != 1);
}

int check_envcnt(const char *str, char *dst)
{
	int ix;
	int ret;
	int quote_flag;

	ix = -1;
	quote_flag = 0;
	dst = ft_strdup(str);
	while (dst[++ix])
	{
		is_inquoted(dst, ix, &quote_flag);
		if (is_errnoflag(dst, ix, quote_flag) && is_envflag(dst, ix, quote_flag))
			ret++;
	}
	if (ret > 0)
		return (TRUE);
	return (FALSE);
}

int setup_and_check_env(char *dst, const char *str, t_data *data)
{
	int ix;
	int quote_flag;

	ix = -1;
	quote_flag = 0;
	if (check_envcnt(str, dst) == TRUE)
	{
		while (dst[++ix])
		{
			is_inquoted(str, ix, &quote_flag);
			trc(dst[ix]);
			if (is_errnoflag(str, ix, quote_flag))
				dst = append_errno(dst, ix, ft_strlen(dst));
			else if (is_envflag(str, ix, quote_flag))
				dst = append_env(dst, ix, ft_strlen(dst), data);
		}
	}
	return (0);
}