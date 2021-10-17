/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:05:46 by jekim             #+#    #+#             */
/*   Updated: 2021/10/17 12:54:20 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parse_envtoken(char *buf)
{
	char	*tkn;
	int		tkn_l;
	int		ix;

	ix = 0;
	tkn_l = 0;
	while (buf[++ix] && (ft_isalpha(buf[ix]) || buf[ix] == '_'))
		tkn_l++;
	if (!tkn_l)
		return (NULL);
	tkn = (char *)ft_calloc(sizeof(char), (tkn_l + 1));
	if (!tkn)
		return (NULL);
	ix = -1;
	while (++ix < tkn_l)
		tkn[ix] = buf[ix + 1];
	tkn[tkn_l] = '\0';
	return (tkn);
}

char	*append_env(char *old_buf, t_envlst *env, int *current_idx, int *buf_l)
{
	char	*ret;
	int		envvar_l;
	int		envkey_l;
	int		ix;

	ix = -1;
	envvar_l = ft_strlen(env->value);
	envkey_l = ft_strlen(env->key);
	ret = (char *)ft_calloc(sizeof(char), *buf_l + envvar_l + 1);
	ft_strlcpy(ret, old_buf, *current_idx + 1);
	ft_strlcpy(ret + *current_idx, env->value, envvar_l + 1);
	while (old_buf[*current_idx + envkey_l + ++ix])
		ret[*current_idx + envvar_l + ix]
			= old_buf[*current_idx + envkey_l + ix + 1];
	*buf_l = ft_strlen(ret);
	*current_idx = *current_idx + (ft_strlen(env->value) - 1);
	free(old_buf);
	return (ret);
}

char	*append_errono(char *old_buf, int *current_idx, int *buf_l)
{
	char	*ret;
	char	*errno_str;
	int		errno_l;
	int		ix;

	ix = -1;
	errno_str = ft_itoa(errno);
	errno_l = ft_strlen(errno_str);
	ret = (char *)ft_calloc(sizeof(char), *buf_l + errno_l + 1);
	ft_strlcpy(ret, old_buf, *current_idx + 1);
	ft_strlcpy(ret + *current_idx, errno_str, errno_l + 1);
	if (*buf_l != (int)ft_strlen(ret))
	{
		while (old_buf[*current_idx + errno_l + ++ix])
			ret[*current_idx + errno_l + ix] = old_buf[*current_idx + ix + 2];
	}
	*buf_l = ft_strlen(ret);
	*current_idx = *current_idx + (errno_l);
	free(errno_str);
	free(old_buf);
	return (ret);
}

void	replace_env(char **buf, int *ix, int *buf_l, t_data *data)
{
	t_envlst	*env;
	char		*env_key;	

	env = NULL;
	env_key = parse_envtoken(*buf + *ix);
	if (env_key)
	{
		env = find_env(env_key, data);
		free(env_key);
	}
	if (env)
		*buf = append_env(*buf, env, ix, buf_l);
	tri(*ix);
}

char	*parse_env(char *buf, t_data *data)
{
	int	ix;
	int	buf_l;
	int	qflag;

	ix = -1;
	buf_l = ft_strlen(buf);
	qflag = 0;
	while (++ix < buf_l)
	{
		trc(buf[ix]);
		is_inquote(buf[ix], &qflag);
		if (buf[ix] == '$' && buf[ix + 1] == '?' && qflag != 1)
			buf = append_errono(buf, &ix, &buf_l);
		else if (buf[ix] == '$' && qflag != 1)
			replace_env(&buf, &ix, &buf_l, data);
	}
	return (buf);
}