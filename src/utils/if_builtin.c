/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 02:03:57 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/07 02:10:26 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	if_builtin(t_token *input)
{
	while (input && (input->type == REDIRECT || input->type == FILEPATH))
		input = input->next;
	if (!input || input->type == PIPE)
		return (1);
	if (ft_strequel(input->content, "cd")
		|| ft_strequel(input->content, "echo")
		|| ft_strequel(input->content, "pwd")
		|| ft_strequel(input->content, "env")
		|| ft_strequel(input->content, "exit")
		|| ft_strequel(input->content, "export")
		|| ft_strequel(input->content, "unset"))
		return (1);
	return (0);
}
