/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_del_nullish_token.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 06:22:20 by jekim             #+#    #+#             */
/*   Updated: 2021/12/08 17:50:12 by jekim            ###   ########.fr       */
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
	t_token	*lst;

	lst = token;
	while (lst->next)
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
		while (lst->content == NULL && lst->ix > 1)
		{
			trs(lst->content);
			tmp = lst->prev;
			free(lst->content);
			free(lst);
			lst = tmp;
		}
		lst->next = NULL;
	}
	return (0);
}