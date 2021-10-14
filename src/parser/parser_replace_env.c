/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:05:46 by jekim             #+#    #+#             */
/*   Updated: 2021/10/14 19:09:56 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char *parse_envtoken(char *buf)
{
	char *tkn;
	int tkn_l;
	int ix;

	ix = 0;
	tkn_l = 0;
	while (buf[++ix] && ft_isalpha(buf[ix]) && buf[ix] == '_')
		tkn_l++;
	if (!tkn_l)
		return (NULL);
	tkn = (char *)malloc(sizeof(char) * (tkn_l + 1));
	if (!tkn)
		return (NULL);
	ft_strlcpy(tkn, buf, tkn_l);
	return (tkn);
}

int env_replacor(char *buf, char *env_var, int idx)
{
	char *new_buf;
	int oldbuf_len;
	int envvar_len;
	int ret;

	ret = 0;
	oldbuf_len = ft_strlen(buf);
	envvar_len = ft_strlen(env_var);
	new_buf = (char *)malloc(sizeof(char) + (oldbuf_len + envvar_len + 1));
	if (!new_buf)
		return (0);
	new_buf[oldbuf_len + envvar_len] = '\0';
	ft_memcpy(new_buf, buf, idx);
	ft_memcpy(new_buf + idx, env_var, envvar_len);
	ft_memcpy(new_buf + idx + envvar_len, buf + idx, oldbuf_len - idx);
	free(env_var);
	free(buf);
	buf = new_buf;
	return (envvar_len);
}

int replace_env(char *buf, t_data *data)
{
	int ix;
	int qflag;
	char *envtoken;
	char *env_var;
	
	ix = 0;
	qflag = 0;
	while (buf[ix])
	{
		is_inquote(buf, &qflag);
		if (buf[ix] == '$' && qflag != 1)
		{
			envtoken = parse_envtoken(buf);
			env_var = get_env(envtoken, data);
			if (!envtoken)
				;
			else if (!env_var)
				ix += ft_strlen(envtoken);
			else
				ix += env_replacor(buf, env_var, ix);
			if (envtoken)
				free(envtoken);
		}
		ix++;
	}
	return (0);
}


// 인덱스를 찾고
// 버퍼에 $가 있고, 이 뒤에 있는 스트링이 환경변수면 치환
// 하지만 스페이스기준으로 잘라진 스트링이 환경변수가 아니라면
// 없는 것으로 여기고 $-> 삭제 -- echo "hi-[$HOMEhihi]-hi" // hi-[]-hi