/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_del_nullish_token.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:22:20 by jekim             #+#    #+#             */
/*   Updated: 2021/12/05 07:40:42 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int get_token_l(t_token *token)
{
	t_token	*lst;
	int		ret;

	ret = 0;
	lst = token;
	while (lst != NULL)
	{
		ret++;
		lst = lst->next;
	}
	return (ret);
}

t_token *get_last_token(t_token *token)
{
	int		ix;
	t_token	*lst;

	ix = 0;
	lst = token;
	while (lst)
		lst = lst->next;
	return (lst);
}

int delete_nullish_token(t_token *token)
{
	int		token_l;
	t_token	*lst;
	t_token *tmp;

	token_l = get_token_l(token);
	if (token_l == 0)
		return (0);
	else
	{
		lst = get_last_token(token);
		while (lst)
		{
			tri(lst->ix);
			if (lst->content)
				break ;
			tmp = lst->prev;
			free(token);
			lst = tmp;
		}
	}
	return (0);
}