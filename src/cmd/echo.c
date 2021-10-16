/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:54:11 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 13:54:10 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

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
	if (tree && tree->contents)
		ft_putstr_fd(tree->contents, 1);
	write(1, "\n", 1);
}

static int	echo_nflag(t_token *tree)
{
	if (tree && tree->contents)
		ft_putstr_fd(tree->contents, 1);
}

int	minishell_echo(t_data *data)
{
	if (echo_if_nnn(data->input->next->contents)) //flag 변수 이름 바꿔야
		echo_nflag(data->input->next);
	else
		echo_noflag(data->input->next);
}
