/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:54:11 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/07 18:34:27 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	echo_if_nnn(char *flag)
{
	if (*flag != '-')
		return (0);
	flag++;
	while (*flag)
	{
		if (*flag != 'n')
			return (0);
		flag++;
	}
	return (1);
}

static int	echo_noflag(t_token *input, int ofd)
{
	while (input && input->type != PIPE)
	{
		if (input->type != REDIRECT && input->type != FILEPATH)
		{
			ft_putstr_fd(input->content, ofd);
			if (input->next && input->next->type != PIPE)
				write(ofd, " ", 1);
		}
		input = input->next;
	}
	write(ofd, "\n", 1);
	return (0);
}

static int	echo_nflag(t_token *input, int ofd)
{
	while (input && input->type != PIPE)
	{
		if (input->type != REDIRECT && input->type != FILEPATH)
		{
			ft_putstr_fd(input->content, ofd);
			if (input->next && input->next->type != PIPE)
				write(ofd, " ", 1);
		}
		input = input->next;
	}
	return (0);
}

int	minishell_echo(t_token *input, int ofd)
{
	input = input->next;
	if (!input || input->type == PIPE)
		return (0);
	if (input->type == FLAG && echo_if_nnn(input->content))
	{
		input = input->next;
		return (echo_nflag(input, ofd));
	}
	else
		return (echo_noflag(input, ofd));
}
