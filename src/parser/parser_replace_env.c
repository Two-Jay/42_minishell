/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_replace_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 12:05:46 by jekim             #+#    #+#             */
/*   Updated: 2021/10/14 13:00:47 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// 인덱스를 찾고
// 버퍼에 $가 있고, 이 뒤에 있는 스트링이 환경변수면 치환
// 하지만 스페이스기준으로 잘라진 스트링이 환경변수가 아니라면
// 없는 것으로 여기고 $-> 삭제 -- echo "hi-[$HOMEhihi]-hi" // hi-[]-hi
char *parse_envtoken(char *buf)
{
	char *tkn;
	int tkn_l;
	int ix;

	ix = 0;
	tkn_l = 0;
	while (buf[++ix] && ft_isalpha(buf[ix]) && buf[ix] == '_')
		tkn_l++;
	tkn = (char *)malloc(sizeof(char) * (tkn_l + 1));
	if (!tkn)
		return (NULL);
	ft_strlcpy(tkn, buf, tkn_l);
	return (tkn);
}

int replace_env(char *buf, t_data *data)
{
	int ix;
	char *envtoken;
	
	ix = 0;
	while (buf[ix])
	{
		tri(ix);
		if (buf[ix] == '$')
		{
			envtoken = parse_envtoken(buf);
			trs(envtoken);
			free(envtoken);
		}
		ix++;
	}
	return (0);
}