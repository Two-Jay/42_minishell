/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:54:11 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/12 13:39:24 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

int	echo_noflag(t_token *tree, t_token *envp)
{
	int	len;

	if (tree && tree->contents)
	{
		len = ft_strlen(tree->contents);
		write(1, tree->contents, len);
	}
	write(1, "\n", 1);
}

int	echo_nflag(t_token *tree, t_token *envp)
{
	int	len;

	if (tree && tree->contents)
	{
		len = ft_strlen(tree->contents);
		write(1, tree->contents, len);
	}
}

int	minishell_echo(t_token *tree, t_token *envp)
{
	if (ft_strnstr(tree->flag, "-n", 2)) //flag 변수 이름 바꿔야
		echo_nflag(tree->next, envp);
	else
		echo_noflag(tree->next, envp);
}
