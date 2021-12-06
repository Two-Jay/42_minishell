/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:44:49 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/07 00:59:40 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_argument(t_token *input)
{
	if (!input->next || input->next->type == PIPE)
		return (ARGUMENT_X);
	input = input->next;
	while (input->type == REDIRECT || input->type == FILEPATH)
		input = input->next;
	if (check_flag(input))
		return (FLAG_O);
	if (!input || input->type == PIPE)
		return (ARGUMENT_X);
	return (ARGUMENT_O);
}
