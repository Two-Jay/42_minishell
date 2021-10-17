/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:48:48 by jekim             #+#    #+#             */
/*   Updated: 2021/10/18 00:17:09 by jekim            ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_split_buflen(char *buf)
{
	int ix;
	int qflag;
	int ret;

	ix = 0;
	qflag = 0;
	ret = 0;
	while (buf[ix])
	{
		is_inquote(buf[ix], &qflag);
		if (!ft_isspace(buf[ix]) 
			&& (buf[ix + 1] == '\0' || ft_isspace(buf[ix + 1]))
			&& !qflag)
			ret++;
		ix++;
	}
	tri(ret);
	return (ret);
}

int ft_strlen_til_space(char *buf, int idx)
{
	int ret;
	int qflag;

	ret = 0;
	qflag = 0;
	while (buf[idx])
	{
		is_inquote(buf[idx], &qflag);
		if (ft_isspace(buf[idx]) && !qflag)
			break ;
		ret++;
		idx++;
	}
	tri(ret);
	return (ret);
}

char **tokenize_input(char *buf, t_data *data)
{
	char	**ret;
	int		ix;
	int		jx;
	int		tkn_l;
	int		ret_l;

	ix = 0;
	jx = 0;
	(void)data;
	trs(buf);
	ret_l = get_split_buflen(buf);
	ret = (char **)malloc(sizeof(char *) * (ret_l + 1));
	if (!ret)
		return (NULL);
	while (buf[ix])
	{
		tkn_l = ft_strlen_til_space(buf, ix);
		ret[jx] = (char *)ft_calloc(sizeof(char), (tkn_l + 1));
		ft_strlcpy(ret[jx], &buf[ix], tkn_l + 1);
		ret[jx][tkn_l] = '\0';
		ix += tkn_l + 1;
		jx++;
		tri(ix);
	}
	ret[jx] = NULL;
	ix = 0;
	while (ret[ix])
		trs(ret[ix++]);
	return (ret);
}