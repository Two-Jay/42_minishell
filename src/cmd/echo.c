/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:54:11 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/20 22:56:52 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

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

static int	echo_noflag(t_token *tree)
{
	while (tree)
	{
		ft_putstr_fd(tree->content, 1);
		write(1, " ", 1);
		tree = tree->next;
	}
	write(1, "\n", 1);
	// $? 0으로 세팅
	return (0);
}

static int	echo_nflag(t_token *tree)
{
	while (tree)
	{
		ft_putstr_fd(tree->content, 1);
		write(1, " ", 1);
		tree = tree->next;
	}
	// $? 0으로 세팅
	return (0);
}

int	minishell_echo(t_data *data)
{
	t_token	*tree;
	int		return_value;

	tree = data->input->next;
	if (echo_if_nnn(tree->content))
	{
		tree = tree->next;
		return (echo_nflag(tree));
	}
	else
		return (echo_noflag(tree));
}
