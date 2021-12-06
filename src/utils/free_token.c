/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:56:40 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/06 22:05:50 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	free_token(t_token *input)
{
	t_token	*tree;

	tree = input->next;
	while (tree && tree->next)
	{
		if (tree->prev->content)
			free(tree->prev->content);
		free(tree->prev);
		tree = tree->next;
	}
	free(tree->content);
	free(tree);
	return (0);
}
