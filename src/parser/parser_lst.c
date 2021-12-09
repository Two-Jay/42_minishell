/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:12:08 by jekim             #+#    #+#             */
/*   Updated: 2021/12/09 12:20:05 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *create_input_token(char *str, int ix)
{
	t_token *ret;

	ret = (t_token *)malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->content = str;
	ret->ix = ix;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

int set_dummy_head_lst(t_data *data)
{
	t_token *tmp;
	
	tmp = create_input_token(NULL, 0);
	if (!tmp)
		return (ERROR_OCCURED);
	data->input = tmp;
	return (0);
}

int build_input_token_lst(char **split_ret, t_data *data)
{
	int		ix;
	char	*token_value;
	t_token	*lst;
	t_token	*tmp;
	int		token_l;

	ix = -1;
	token_l= 0;
	token_value = NULL;
	if (set_dummy_head_lst(data))
		return (ERROR_OCCURED);
	lst = data->input;
	while (split_ret[++ix])
	{
		token_value = quote_trim(split_ret[ix], data);
		trs(token_value);
		if (token_value != NULL && ft_strlen(token_value) != 0)
		{
			tmp = create_input_token(token_value, ix + 1);
			tmp->prev = lst;
			lst->next = tmp;
			lst = tmp;
		}
		token_l++;
	}
	return (0);
}