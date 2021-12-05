/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:26:45 by jiychoi           #+#    #+#             */
/*   Updated: 2021/12/05 14:06:45 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd.h"

char	*ft_strndup(char *str, int length)
{
	char	*ptr;
	char	*ptr_backup;

	ptr = (char *)malloc(sizeof(char) * (length + 1));
	if (!ptr)
		return (0);
	ptr_backup = ptr;
	while (length--)
		*ptr++ = *str++;
	*ptr = 0;
	return (ptr_backup);
}
