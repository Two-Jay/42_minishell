/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/10 15:54:11 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/10 16:53:56 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

int	echo_noflag(char *str, char *flag, char *envp[])
{

}

int	echo_nflag(char *str, char *flag, char *envp[])
{

}

int	minishell_echo(node *tree, char *envp[])
{
	if (ft_strnstr(flag, "-n", 2))
		echo_nflag(str, flag, envp);
	else
		echo_noflag(str, flag, envp);
}
