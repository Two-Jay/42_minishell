/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:54:11 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/12 11:10:13 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"


int	echo_noflag(node *tree, node *envp)
{

}

int	echo_nflag(node *tree, node *envp)
{

}

int	minishell_echo(node *tree, node *envp)
{
	if (ft_strnstr(tree->next->data, "-n", 2))
		echo_nflag(tree, envp);
	else
		echo_noflag(tree, envp);
}
