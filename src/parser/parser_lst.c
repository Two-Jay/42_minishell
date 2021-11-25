/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:12:08 by jekim             #+#    #+#             */
/*   Updated: 2021/11/26 03:43:08 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token *create_input_token(const char *str, int ix)
{
	t_token *ret;

	ret = (t_token *)malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->content = NULL;
	if (str && *str)
		ret->content = ft_strdup(str);
	ret->ix = ix;
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
	int ix;
	t_token	*lst;
	t_token	*tmp;

	ix = -1;
	if (set_dummy_head_lst(data))
		return (ERROR_OCCURED);
	lst = data->input;
	while (split_ret[++ix])
	{
		tmp = create_input_token(split_ret[ix], ix + 1);
		// assign_input_token_type(tmp);
		tmp->prev = lst;
		lst->next = tmp;
		lst = tmp;
	}
	return (0);
}