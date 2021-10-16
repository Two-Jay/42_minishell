/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 19:12:04 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/16 20:22:47 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

char	*export_equal_check(char *str)
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
		return (0);
	return (ptr_equal);
}

int	export_name_check(char *str, char *ptr_equal)
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
