/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 11:07:53 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/12 11:09:52 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

static int	echo_getenv_len(char *str)
{
	int	len;

	while (*str)
	{
		if (*str == '$')
		{
			while (*str != ' ' && *str != 0)
			{
				len++;
				str++;
			}
			break ;
		}
		str++;
	}
	return (len);
}

char	*echo_getenv(char *str)
{
	int		len;
	int		i;
	char	*env_name;

	if (!str)
		return (0);
	len = echo_getenv_len(str);
	env_name = malloc(sizeof(char) * len + 1);
	if (!env_name)
		return (0);
	i = 0;
	while (*str != ' ' && *str != 0)
	{
		env_name[i++] = *str;
		str++;
	}
	env_name[i] = 0;
	return (env_name);
}

//pseudo-code
t_envlist ()
