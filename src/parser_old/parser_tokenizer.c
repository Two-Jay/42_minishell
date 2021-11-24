/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 14:48:48 by jekim             #+#    #+#             */
/*   Updated: 2021/11/21 20:07:07 by jekim            ###   ########.fr       */
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
	return (ret);
}

int free_all(char **bucket, int ix, int error_flag)
{
	while (bucket[ix])
		free(bucket[ix++]);
	free(bucket);
	bucket = NULL;
	return (error_flag);
}

void fill_splited_token(char **ret, char *buf)
{
	int ix;
	int jx;
	int tkn_l;

	ix = 0;
	jx = 0;
	tkn_l = 0;
	while (buf[ix])
	{
		tkn_l = ft_strlen_til_space(buf, ix);
		ret[jx] = (char *)ft_calloc(sizeof(char), (tkn_l + 1));
		if (!ret[jx])
			free_all(ret, jx, 1);
		ft_strlcpy(ret[jx], &buf[ix], tkn_l + 1);
		ret[jx][tkn_l] = '\0';
		ix += tkn_l + 1;
		jx++;
	}
	ret[jx] = NULL;
}

void print_ret(char **ret)
{
	int ix;

	ix = 0;
	while (ret[ix])
		trs(ret[ix++]);
}

int create_token(char **splited, t_data *data)
{
	int ix;
	int tkn_l;
	t_state state;
	t_token *tknp;

	ix = 0;
	state = NOT_PARSERED;
	while (ix && splited[ix])
	{
		tkn_l = ft_strlen(splited[ix]);
		tknp = (t_token *)ft_calloc(sizeof(t_token), 1);
		tknp->content = ft_strdup(splited[ix]);
		tknp->idx = ix;
		tknp->type = state;
		if (ix == 0)
			data->input = tknp;
		else
			tknp = tknp->next;
	}
	return (0);
}

int tokenize_input(char *buf, t_data *data)
{
	char	**splited;
	int		ix;
	int		jx;
	int		ret_l;

	ix = 0;
	jx = 0;
	(void)data;
	trs(buf);
	ret_l = get_split_buflen(buf);
	splited = (char **)malloc(sizeof(char *) * (ret_l + 1));
	if (!splited)
		return (ERROR_OCCURED);
	fill_splited_token(splited, buf);
	print_ret(splited);
	// if (ft_strequel(splited[0], ""))
	// 	return (catch_emptystr());
	return (free_all(splited, jx, 0));
}