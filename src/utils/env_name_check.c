/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_name_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 16:38:57 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

char	*env_equal_check(char *str)
{
	char	*ptr_equal;

	ptr_equal = str;
	while (*ptr_equal)
	{
		if (*ptr_equal == '=')
			break ;
		ptr_equal++;
	}
	if (!*ptr_equal)
		return (NULL);
	return (ptr_equal);
}

int	env_name_check(char *str, char *ptr_equal)
{
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	str++;
	if (ptr_equal)
	{
		while (*str < *ptr_equal)
		{
			if (!ft_isalnum(*str) && *str != '_')
				return (0);
			str++;
		}
		return (1);
	}
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '_')
			return (0);
		str++;
	}
	return (1);
}
