/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiychoi <jiychoi@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 13:06:34 by jiychoi           #+#    #+#             */
/*   Updated: 2021/10/20 13:39:20 by jiychoi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cmd2.h"

int	check_flag(t_data *data)
{
	char	*str;

	if (!data->input->next)
		return (0);
	str = data->input->next->content;
	if (*str == '-' && ft_isalpha(*(str + 1)))
		return (1);
	return (0);
}
