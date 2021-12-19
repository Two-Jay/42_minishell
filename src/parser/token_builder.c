/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_builder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <arabi1549@naver.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 17:12:08 by jekim             #+#    #+#             */
/*   Updated: 2021/12/19 17:35:00 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_token	*create_input_token(char *str, int ix)
{
	t_token	*ret;

	ret = (t_token *)malloc(sizeof(t_token));
	if (!ret)
		return (NULL);
	ret->content = str;
	ret->ix = ix;
	ret->next = NULL;
	ret->prev = NULL;
	return (ret);
}

int	set_dummy_head_lst(t_data *data)
{
	t_token	*tmp;

	tmp = create_input_token(NULL, 0);
	if (!tmp)
		return (ERROR_OCCURED);
	data->input = tmp;
	return (0);
}

char	*quote_checker(char **split_ret, int ix, t_data *data)
{
	char	*token_value;

	token_value = quote_trim(split_ret[ix], data);
	if (token_value == NULL && ft_strlen(token_value) == 0)
		free(token_value);
	return (token_value);
}

int	build_input_token_lst(char **split_ret, t_data *data)
{
	int		ix;
	t_token	*lst;
	t_token	*tmp;
	int		token_l;

	ix = -1;
	token_l = 0;
	if (set_dummy_head_lst(data))
		return (ERROR_OCCURED);
	lst = data->input;
	while (split_ret[++ix])
	{
		tmp = create_input_token(quote_checker(split_ret, ix, data), ix + 1);
		tmp->prev = lst;
		lst->next = tmp;
		lst = tmp;
		token_l++;
	}
	return (0);
}
