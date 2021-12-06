/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 00:44:49 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/07 02:08:28 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_argument(t_token *input)
{
	if (!input->next || input->next->type == PIPE)
		return (ARGUMENT_X);
	input = input->next;
	while (input && (input->type == REDIRECT || input->type == FILEPATH))
		input = input->next;
	if (check_flag(input))
		return (FLAG_O);
	if (!input || input->type == PIPE)
		return (ARGUMENT_X);
	return (ARGUMENT_O);
}

int	check_arg_num(t_token *input)
{
	int	n;

	n = 0;
	if (!input->next || input->next->type == PIPE)
		return (n);
	input = input->next;
	while (input && input->type != PIPE)
	{
		if (input->type == STR || input->type == FLAG)
			n++;
		input = input->next;
	}
	return (n);
}
