/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:56:40 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

int	free_token(t_token *input, int return_status)
{
	t_token	*tree;

	tree = input->next;
	while (tree && tree->next)
	{
		free(tree->prev->content);
		free(tree->prev);
		tree = tree->next;
	}
	free(tree->content);
	free(tree);
	return (return_status);
}
