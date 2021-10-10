/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:54:11 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/10 19:00:17 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

int	echo_noflag(node *tree, char *envp[])
{

}

int	echo_nflag(node *tree, char *envp[])
{

}

int	minishell_echo(node *tree, char *envp[])
{
	if (ft_strnstr(tree->next->data, "-n", 2))
		echo_nflag(tree, flag, envp);
	else
		echo_noflag(str, flag, envp);
}
