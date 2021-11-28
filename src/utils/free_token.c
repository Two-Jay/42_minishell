/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/27 00:56:40 by jiychoi           #+#    #+#             */
/*   Updated: 2021/11/27 00:56:54 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	free_token(t_token *input, int return_status)
{
	input = input->next;
	while (input && input->next)
	{
		free(input->prev->content);
		free(input->prev);
		input = input->next;
	}
	free(input->content);
	free(input);
	return (return_status);
}
