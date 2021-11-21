/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:54:24 by jekim             #+#    #+#             */
/*   Updated: 2021/11/21 20:05:43 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void check_isquoted(const char *str, int *flag)
{
	if (*str == 34)
	{
		if (*flag == 2)
			*flag == 0;
		if (*flag == 0)
			*flag == 2;
	}
	if (*str == 39)
	{
		if (*flag == 1)
			*flag == 0;
		if (*flag == 0)
			*flag == 1;	
	}
}

int find_split_point(const char *str, char **startp, char **endp)
{
	int ix;
	int quote_flag;
	int limit;

	ix = 0;
	quote_flag = 0;
	limit = ft_strlen(str);
	if (limit == 0)
		return (ERROR_OCCURED);
	while (ft_isspace(str[ix]))
		ix++;
	*startp = str + ix;
	limit = ft_strlen(*startp);
	while (ix < limit)
	{
		check_isquoted(*startp + ix, &quote_flag);
		if (!quote_flag && ft_isspace(*startp + ix))\
			break ;
		ix++;
	}
	*endp = *startp + ix;
	return (0);
}

int split_by_chunk(const char *str, t_data *data)
{
	int		ix;
	char 	*startp;
	char 	*endp;
	t_token	*token;
	t_token *prev_tmp;

	ix = 0;
	prev_tmp = create_input_token(NULL, &ix);
	data->input = prev_tmp;
	token = data->input->next;
	while (*endp != '\0')
	{
		ix++;
		find_split_point(str, startp, endp); // startp, endp 구하는 함수
		token = create_input_token(ft_strndup(startp, startp - endp), &ix);
		token->prev = prev_tmp;
		token = token->next;
	}
}