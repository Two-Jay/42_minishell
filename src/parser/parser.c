/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jekim <jekim@42seoul.student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 16:22:59 by jekim             #+#    #+#             */
/*   Updated: 2021/11/24 07:59:58 by jekim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int set_input_process_struct(t_data *data)
{
	data->ip = (t_input_process *)malloc(sizeof(t_input_process));
	if (!data->ip)
		return (ERROR_OCCURED);
	return (0);
}

int parse_input_string(const char *str, t_data *data)
{
	if (set_input_process_struct(data)
		|| insert_space_beside_spclcmd(str, data)
		|| split_by_chunk(data->ip->isbs_ret, data))
		return (ERROR_OCCURED);
	return (0);
}