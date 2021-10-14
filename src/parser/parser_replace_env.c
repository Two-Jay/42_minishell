/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:05:46 by jekim             #+#    #+#             */
/*   Updated: 2021/10/14 21:36:06 by jekim            ###   ########.fr       */
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
	while (buf[++ix] && (ft_isalpha(buf[ix]) || buf[ix] == '_'))
		tkn_l++;
	tri(tkn_l);
	if (!tkn_l)
		return (NULL);
	tkn = (char *)malloc(sizeof(char) * (tkn_l + 1));
	if (!tkn)
		return (NULL);
	ix = 0;
	while (ix <= tkn_l)
	{
		tkn[ix] = buf[ix + 1];
		ix++;
	}
	buf[tkn_l] = '\0';
 	return (tkn);
}

char *replace_env(char *buf, t_data *data)
{
	int ix;
	int qflag;
	char *new_buf;
	char *envtoken;
	char *env_var;

	ix = 0;
	qflag = 0;
	new_buf = (char *)malloc(sizeof(char) * (ft_strlen(buf) + 1));
	if (!new_buf)
		return (NULL);
	while (buf[ix])
	{
		is_inquote(buf[ix], &qflag);
		if (buf[ix] == '$')
		{
			envtoken = parse_envtoken(buf + ix);
			if (!envtoken)
				;
			env_var = get_env(envtoken, data);
			if (!env_var)
				;
			trs(env_var);
			trs(envtoken);
		}
		else
			new_buf[ix] = buf[ix];
		ix++;
	}
	trs(new_buf);
	return (new_buf);
}


// 인덱스를 찾고
// 버퍼에 $가 있고, 이 뒤에 있는 스트링이 환경변수면 치환
// 하지만 스페이스기준으로 잘라진 스트링이 환경변수가 아니라면
// 없는 것으로 여기고 $-> 삭제 -- echo "hi-[$HOMEhihi]-hi" // hi-[]-hi