/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:06:34 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/07 01:05:56 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_flag(t_token *input)
{
	if (!input)
		return (0);
	if (input->type == FLAG || input->content[0] == '-')
		return (1);
	return (0);
}

t_token	*find_flag(t_token *input)
{
	if (!input->next || input->next->type == PIPE)
		return (NULL);
	input = input->next;
	while (input->type == REDIRECT || input->type == FILEPATH)
		input = input->next;
	if (check_flag(input))
		return (input);
	return (NULL);
}
