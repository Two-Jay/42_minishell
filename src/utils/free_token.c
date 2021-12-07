/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:56:40 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/07 19:57:37 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_token(t_token *input)
{
	t_token	*token_todel;
	t_token	*token_temp;

	token_temp = input->next;
	while (token_temp->next)
	{
		token_todel = token_temp->prev;
		if (token_todel->content)
			free(token_todel->content);
		free(token_todel);
		token_temp = token_temp->next;
	}
	token_todel = token_temp->prev;
	if (token_todel->content)
		free(token_todel->content);
	free(token_todel);
	free(token_temp->content);
	free(token_temp);
	return (0);
}
